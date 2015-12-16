//
//  Execution_Core.c
//
//
//  Created by Luiz Henrique Campos Barboza on 09/12/15.
//
//
//

#include "LoadClass_core.h"
#include "macros.h"
#include "Heap.h"
#include "Frame.h"
#include "Execution_Core.h"

/**
 *  Description
 *  @brief Execução da JVM
 *  @param pFrame     <#pFrame description#>
 *  @param pClassHeap <#pClassHeap description#>
 *  @param dmSize_ptr <#dmSize_ptr description#>
 *
 *  @return <#return value description#>
 */

dataMSize_t dmSize;
ClassFile *ClassHeap;
Frame *stackFrame;
Heap objHeap;

u4 Execute () {

    Frame *pFrame = &stackFrame[dmSize.stkHeap_size - 1];
    u2 classHeapLength = dmSize.clsHeap_size;


    while (pFrame->retornou == 0 && pFrame != NULL && (pFrame->pc) < pFrame->code_length) {
        uint32_t iterator = pFrame->code[pFrame->pc];
        instructions[iterator].call(pFrame);
    }
    pFrame->retornou = 0;

}

u2 getClassIndex(u1 *class_name) {
    // printf("\n\t\t\tentrou getClassIndex: %s", class_name);
    if (mHeap.classes == NULL) {printf("\n\t\t\tsaiu getClassIndex: %s; toReturn: %d", class_name, -3); return -3;}
    if (class_name == NULL || !strcmp(class_name, "")) {printf("\n\t\t\tsaiu getClassIndex: %s; toReturn: %d", class_name, -2);return -2;}

    for(int i=0; i < mHeap.classes_count; i++){
        char *aux = getName(mHeap.classes[i]);
        if(!strcmp(class_name,aux)){
            return i;
        }
    }
    // printf("\n\t\t\tsaiu getClassIndex: %s; toReturn: %d", class_name, -1);
    return -1;
}

void initialize(int class_index) {
    ClassFile *class = mHeap.classes[class_index];
    struct method_info *clinit = getclinit(class);

    if (clinit == NULL) return; // classe abstrata ou interface

    createFrame(clinit, class);
    Execute();

}

/// aloca e inicializa valores default para os fields estaticos da classe indicada por $index
void prepare(u4 index) {

    for (int j = 0; j < mHeap.classes[index]->fields_count; j++) {
        if (checkIfFieldIsStatic(mHeap.classes[index]->fields[j].access_flag)) {
            mHeap.classes[index]->fields[j].value = 0;
        }
    }
}


int loadParentClasses() {
    ClassFile *class = mHeap.classes[mHeap.classes_count - 1];
    u1 *parentName = getParentName(class);
    int flag = 0;

        if (getClassIndex(parentName) == -1) {

        expandClassArray();
        mHeap.classes[mHeap.classes_count++] = classLoader(getClassPath(basePath, parentName));

        prepare(mHeap.classes_count - 1);
        initialize(mHeap.classes_count - 1);

        if (mHeap.classes[mHeap.classes_count - 1]->super_class != 0) {
            flag = loadParentClasses();
        }

    }
    return flag;
}

/// carrega as interfaces da classe na posicao maquina.classes.size - 1 no array de interfaces da area de metodo
int loadInterfaces(ClassFile *class) {
    int interfacesCount = class->interfaces_count;

    for(int i=0; i < interfacesCount; i++){
        u1 *name = getInterfaceName(class, i);

        if (getInterfaceIndex(name) == -1) {
            expandInterfaceArray();
            mHeap.interfaces[mHeap.interfaces_count++] = classLoader(getClassPath(basePath, name));
        }

    }

    // free(cl);
    return 1;
}


int loadClass(u1 *name) {

    if(name == NULL){
        return -1;
    }

    if (strchr(name, '$')) {
        //error(E_DOLAR_NOT_SUPPORTED);
    }

    int toReturn = -1;
    if ((toReturn = getClassIndex(name)) <= -1) {

        toReturn = mHeap.classes_count;
        expandClassArray();
        mHeap.classes[mHeap.classes_count++] = classLoader(getClassPath(basePath, name));

        prepare(mHeap.classes_count - 1);
        initialize(mHeap.classes_count-1);

        loadParentClasses(); // insere em maquina.classes todas as classes pai ainda nao carregadas em maquina.clasess
        loadInterfaces(mHeap.classes[toReturn]); // insere em maquinas.interfaces todas as interfaces ainda nao carregadas em maquina.interfaces

    }

    return toReturn;
}

/*!
	retorna a concatenacao do nome qualificado da classe com base_path e com .class
 */
char* getClassPath(char* base_path, char* class_name) {
    char* path = (char*)malloc(strlen(base_path)+strlen(class_name) + 8);
    if (strstr(class_name,".class") != NULL) {
        if (strlen(base_path)==0)
            sprintf(path, "%s%s", base_path, class_name);
        else
            sprintf(path, "%s/%s", base_path, class_name);
        return path;
    }
    else if (!strcmp(class_name,"java/lang/Object")
             || !strcmp(class_name,"java/lang/System")
             || !strcmp(class_name,"java/io/PrintStream")
             || !strcmp(class_name,"java/lang/String")) {

        sprintf(path, "%s.class", class_name);
        return path;
    } else {
        sprintf(path, "%s/%s.class", base_path, class_name);
        return path;
    }
}

/// retorna um index para o array de classes da area de metodos
int getClassIndex(u1 *class_name) {
    if (mHeap.classes == NULL) {
        return -3;
    }
    if (class_name == NULL || !strcmp(class_name, "")) {
        return -2;
    }

    for(int i=0; i < mHeap.classes_count; i++){
        u1 *aux = getClassNameUtf8(mHeap.classes[i], mHeap.classes[i]->this_class);
        if(!strcmp(class_name,aux)){
            return i;
        }
    }
    return -1;
}

/// retorna um index para o array de interfaces da area de metodos
int getInterfaceIndex(char* interface_name) {
    if (mHeap.classes == NULL) return -1;
    if (interface_name == NULL || !strcmp(interface_name, "")) return -2;

    for(int i=0; i < mHeap.interfaces_count; i++){
        char *aux = mHeap.interfaces[i]->getName(mHeap.interfaces[i]);
        if(!strcmp(interface_name,aux)){
            return i;
        }
    }

    return -1;
}

/// checa se o field é estático
int checkIfFieldIsStatic(uint16_t access_flags) {
    if ((access_flags &  0x0008) == 0x0008)
        return 1;
    else
        return 0;
}

/// realoca o array de classes por 10 (precaução contra memory corruption)
void expandClassArray() {
    ClassFile** tmp;
    tmp = (ClassFile **) realloc(mHeap.classes,(mHeap.classes_count + 10)*sizeof(ClassFile *));

    if (tmp == NULL) {
        exit(-1000);
    }

    mHeap.classes = tmp;
}

/// realoca o array de interfaces por 10 (precaução contra memory corruption)
void expandInterfaceArray() {
    ClassFile ** tmp;
    tmp = (ClassFile **)realloc(mHeap.interfaces,(mHeap.interfaces_count+10)*sizeof(ClassFile*));

    if (tmp == NULL) {
        printf("\nexpandInterfaceArray(): MEMORY CORRUPTION");
        exit(-1000);
    }

    mHeap.interfaces = tmp;
}

/// procura pela presenca do metodo clinit na classe $class
method_info* getclinit(ClassFile *class) {
    // printf("\n\tentrou getclinit: %s", class->getName(class));
    for (int i = 0; i < class->methods_count; i++) {
        char* name = getUtf8String(class->constant_pool, class->methods[i].name_index);
        char* desc = getUtf8String(class->constant_pool, class->methods[i].descriptor_index);

        if (!strcmp(name, "<clinit>") && !strcmp(desc, "()V")) {
            return &(class->methods_pool->methods[i]);
        }
    }
    // printf("\n\tsaiu getclinit%s", class->getName(class));
    return NULL;
}

/*!
	procura e devolve o metodo MAIN
 */
method_info* getMainMethod() {
    CLASS *main_class;
    char *name, *desc;

    main_class = mHeap.classes[0];

    /* procura por método main ([LJava/lang/String;)V */
    for (int i = 0; i < main_class->methods_count; i++){
        name = getUtf8String(main_class->constant_pool, main_class->methods[i].name_index);
        desc = getUtf8String(main_class->constant_pool, main_class->methods[i].descriptor_index);

        if ((strcmp("main", name) == 0) && (strcmp("([Ljava/lang/String;)V", desc) == 0))
            return &(main_class->methods_pool->methods[i]);
    }

    return NULL;
}


u1 *getClassNameUtf8(ClassFile *pClass, u2 classIndexTemp) {
    u1 *bytes;
    u2 nameIndex;

    nameIndex = pFrame->pClass->constant_pool[classIndexTemp - 1].info.CONSTANT_Class_info.name_index;
    bytes = pCLass->constant_pool[nameIndex - 1].info.CONSTANT_Utf8_info.bytes;

    return bytes;
}

u1 *getParentName(Classfile *class) {
    return getClassNameUtf8(class, class->super_class);
}

/*!
	devolve o nome de uma interface recebida
 */
u1* getInterfaceName(ClassFile *class, int interface_index) {
    return getClassNameUtf8(class, class->interfaces[interface_index]);
}


/**
 *  <#Description#>
 *
 *  @param name               <#name description#>
 *  @param pField             <#pField description#>
 *  @param static_values_size <#static_values_size description#>
 *
 *  @return <#return value description#>
 */
//
Field_Value *getFieldValue(u1 *name, Field_Value *pField, u2 static_values_size) {
    u2 count = 0;
    u2 found = 0;

    while (count < static_values_size && found == 0) {
        if (strcmp(pField[count].field_name, name) == 0) {
            found = 1;
        }
        else {
            ++count;
        }
    }
    return &pField[count];
}


u4 *getFieldIndex(u1 *name, Field_Value *pField, u2 static_values_size) {
    u4 count = 0;
    u2 found = 0;

    while (count < static_values_size && found == 0) {
        if (strcmp(pField[count].field_name, name) == 0) {
            found = 1;
        }
        else {
            ++count;
        }
    }
    return count;
}


/**
 *  @brief Retorna uma string referente a um tipo UTF8 na pool de constantes
 *
 *  @param nIndex <#nIndex description#>
 *  @param pool   <#pool description#>
 *
 *  @return <#return value description#>
 */
u1 *GetStringFromConstPool(u2 nIndex, cp_info *pool) {
    u1 *string;

    string = pool[nIndex - 1].info.CONSTANT_Utf8_info.bytes;
    return string;

}

/**
 *  <#Description#>
 *
 *  @param index <#index description#>
 *  @param pool  <#pool description#>
 *
 *  @return Retorna a string referente ao nome do Field
 */
u1 *getFieldName(u2 index, cp_info *pool) { //3
    u2 nameAndType_index = 0;
    u2 name_index;
    u1 *string;

    nameAndType_index = pool[index -1].info.CONSTANT_FieldMethodIMethod_info.name_and_type_index; //24
    name_index = pool[nameAndType_index -1].info.CONSTANT_NameAndType_info.name_index;
    string = GetStringFromConstPool(name_index, pool);

    return string;
}

MethodHeap *initMethodHeap() {
    MethodHeap *mHeap = (MethodHeap *) malloc(sizeof(MethodHeap));

    mHeap.classes = (ClassFile **) malloc(sizeof(ClassFile*));
    mHeap.interfaces = (ClassFile **) malloc(sizeof(ClassFile*));
    mHeap.classes_count = 0;
    mHeap.interfaces_count = 0;

    return mHeap;
}

u1 *getUtf8String(cp_info *pool, int index) {
    if (index == 0) {
        return NULL;
    }
    return (u1 *)pool[index - 1].info.CONSTANT_Utf8_info.bytes;
}

method_info* getclinit(ClassFile *class) {
    for (int i = 0; i < class->methods_count; i++) {
        u1 *name = getUtf8String(class->constant_pool, class->methods[i].name_index);
        u1 *desc = getUtf8String(class->constant_pool, class->methods[i].descriptor_index);

        if (!strcmp(name, "<clinit>") && !strcmp(desc, "()V")) {
            return &(class->methods_pool->methods[i]);
        }
    }
    return NULL;
}

/*!
	procura e devolve o metodo MAIN
 */
method_info* getMainMethod() {
    CLASS *main_class;
    char *name, *desc;

    main_class = mHeap->classes[0];

    /* procura por método main ([LJava/lang/String;)V */
    for (int i = 0; i < main_class->methods_count; i++){
        name = _MCONSTANTP.getUtf8String(main_class->constant_pool, main_class->methods_pool->methods[i].name_index);
        desc = _MCONSTANTP.getUtf8String(main_class->constant_pool, main_class->methods_pool->methods[i].descriptor_index);

        if ((strcmp("main", name) == 0) && (strcmp("([Ljava/lang/String;)V", desc) == 0))
            return &(main_class->methods_pool->methods[i]);
    }

    return NULL;
}

method_info *getMethodByNameDesc(ClassFile *main_class, ClassFile *name_type_class, uint16_t name_type_index) {
    int i;
    u1 *m_name, *m_desc;
    u2 m_name_len, m_desc_len;
    u1 *name, *desc;
    u2 name_len, desc_len;

    name = getUtf8String(name_type_class->constant_pool, name_type_class->constant_pool[name_type_index - 1].info.CONSTANT_NameAndType_info.name_index);
    name_len = strlen(name);
    desc = getUtf8String(name_type_class->constant_pool, name_type_class->constant_pool->constants[name_type_index - 1].info.CONSTANT_NameAndType_info.descriptor_index);
    desc_len = strlen(desc);

    for(i = 0; i < main_class->methods_count; i++) {

        m_name = main_class->constant_pool[(main_class->methods[i].name_index - 1)].info.CONSTANT_Utf8_info.bytes;
        m_name_len = strlen(main_class->constant_pool[(main_class->methods[i].name_index - 1)].info.CONSTANT_Utf8_info.bytes);
        m_desc = main_class->constant_pool[(main_class->methods[i].descriptor_index - 1)].info.CONSTANT_Utf8_info.bytes;
        m_desc_len = strlen(main_class->constant_pool[(main_class->methods[i].descriptor_index - 1)].info.CONSTANT_Utf8_info.bytes);

        if(name_len != m_name_len) {
            continue;
        }
        if(desc_len != m_desc_len) {
            continue;
        }
        if((strncmp((char *)name,(char *)m_name , m_name_len) == 0) &&(strncmp((char *)desc,(char *)m_desc , m_desc_len) == 0)) {
            return &(main_class->methods[i]);
        }

    }
    return NULL;
}

i4 getNumParameters(ClassFile *class, method_info *method) {
    i4 i;
    i4 parametros = 0;
    u2 length;
    u1 *bytes;

    bytes = class->constant_pool[(method->descriptor_index - 1)].info.CONSTANT_Utf8_info.bytes;
    length = strlen(class->constant_pool[(method->descriptor_index - 1)].info.CONSTANT_Utf8_info.bytes);
    for(i = 0; i < length && bytes[i] != ')'; i++) {
        if(bytes[i] == 'L') {
            while(bytes[i] != ';') {
                i++;
            }
            parametros++;
        }else if (bytes[i] == '[') {
            parametros++;
            while(bytes[i] != ';' && bytes[i] != ')') {
                i++;
            }
        } else if((bytes[i] == 'B')||(bytes[i] == 'C')||(bytes[i] == 'F')|| (bytes[i] == 'I')||(bytes[i] == 'S')||(bytes[i] == 'Z') ) {
            parametros++;
        } else if((bytes[i] == 'D')||(bytes[i] == 'J')) {
            parametros+=2;
        }
    }

    return parametros;
}

u8 getObjectField(struct _object *object, u4 field_index) {
    return object->fields[field_index];
}

/*!
	seta um valor a um field que estah instanciado
 */
void setObjectField(struct _object *object, u4 field_index, u8 value) {
    object->fields[field_index] = value;
}

ClassFile *getClassByName(u1 *classname){
    int flag = getClassIndex(classname);
    if (flag < 0) return NULL;
    return mHeap.classes[getClassIndex(classname)];
}


u4 getFieldIndex(char *className, char *name, u2 nameLen, char *desc, u2 descLen) {

    u4 i;
    ClassFile *main_class;
    u1 *getName, *getDesc;

    main_class = getClassByName(className);

    if (!main_class) {
        return -2;
    }

    for (i = 0; main_class && i < main_class->fields_count; i++) {
        getName = main_class->constant_pool[(main_class->fields[i].name_index - 1)].info.CONSTANT_Utf8_info.bytes;
        getDesc = main_class->constant_pool[(main_class->fields[i].descriptor_index - 1)].info.CONSTANT_Utf8_info.bytes;

        if ((strcmp((char *)name, (char *)getName) == 0) && (strcmp((char *)desc, (char *)getDesc) == 0)) {
            return i;
        }
    }

    return -1;
}


u8 getStaticFieldVal(u4 class_index, u4 field_index){
    return mHeap.classes[class_index]fields[field_index].value;
}

/*!
	atribui um valor a um field estatico
 */
void setStaticFieldVal(u4 class_index, u4 field_index, u8 value){
    mHeap.classes[class_index]->fields[field_index].value = value;
}

/*!
	pesquisa um valor de field de uma classe do method_area
 */
u4 searchStaticFieldVal(u4 class_index, char* name,char* desc){

    for(int i =0; i < mHeap.classes[class_index]->fields_count; i++){

        field_info *var = &(mHeap.classes[class_index]->fields[i]);
        char* fieldName = getUtf8String(mHeap.classes[class_index]->constant_pool, var->name_index);
        char* fieldDesc = getUtf8String(mHeap.classes[class_index]->constant_pool, var->descriptor_index);

        if ((strcmp(name,fieldName) == 0) && (strcmp(desc,fieldDesc) == 0)) {
            return i;
        }

    }

    return -1;
}
