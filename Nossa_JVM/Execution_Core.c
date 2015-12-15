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
u4 Execute (Frame *stackFrame_ptr, ClassFile *pClassHeap, dataMSize_t *dmSize_ptr) {
    
    Frame *pFrame = &stackFrame_ptr[dmSize_ptr->stkHeap_size - 1];
    u2 classHeapLength = dmSize_ptr->clsHeap_size;
    u4 *local_iterator = pFrame->local;
    u1 *code_iterator;
    i4 error = 0;
    i8 longVal;
    u2 i, class_index, nameAndType_index;
    u1 *strName;
    u1 *strDesc;
    u1 *class_name;
    Field_Value *fv;
    u4 field_index;
    u1 *field_name;
    ClassFile *pClass;
    u2 nIndex;
    method_info *method;
    u2 class_name_index;
    
    code_iterator = pFrame->code + pFrame->pc;
    
    while (pFrame->pc < pFrame->code_length) {
        switch (code_iterator[pFrame->pc]) {
            case op_nop:
                pFrame->pc++;
                break;
                
                ///////////////// Stack Operations ////////////////
                //Instructions that push a constant onto the stack
     

        }
    }
}

u2 getClassIndex(u1 *class_name) {
    // printf("\n\t\t\tentrou getClassIndex: %s", class_name);
    if (maquina.method_area->classes == NULL) {printf("\n\t\t\tsaiu getClassIndex: %s; toReturn: %d", class_name, -3); return -3;}
    if (class_name == NULL || !strcmp(class_name, "")) {printf("\n\t\t\tsaiu getClassIndex: %s; toReturn: %d", class_name, -2);return -2;}
    
    for(int i=0; i < maquina.method_area->classes_count; i++){
        char *aux = maquina.method_area->classes[i]->getName(maquina.method_area->classes[i]);
        if(!strcmp(class_name,aux)){
            return i;
        }
    }
    // printf("\n\t\t\tsaiu getClassIndex: %s; toReturn: %d", class_name, -1);
    return -1;
}

static void initialize(int class_index) {
    ClassFile *class = maquina.method_area->classes[class_index];
    struct _method_info* clinit = getclinit(class);
    
    if (clinit == NULL) return; // classe abstrata ou interface
    
    construirFrame(class, clinit);
    execute();
    
}

/// aloca e inicializa valores default para os fields estaticos da classe indicada por $index
static void prepare(uint32_t index) {
    
    for (int j = 0; j < maquina.method_area->classes[index]->fields_count; j++) {
        if (checkIfFieldIsStatic(maquina.method_area->classes[index]->fields_pool->fields[j].access_flags)) {
            maquina.method_area->classes[index]->fields_pool->fields[j].value = 0;
        }
    }
}


/// verifica, prepara e opcionalmente resolve
static void link(int class_index) {
    prepare(class_index);
}

static int loadParentClasses() {
    CLASS* class = maquina.method_area->classes[maquina.method_area->classes_count-1];
    char* parentName = _MCLASS.getParentName(class);
    int flag = 0;
    
    // insere parent em maquina.method_area->classes caso parent ainda nao esteja carregado
    if (getClassIndex(parentName) == -1) {
        
        expandClassArray();
        maquina.method_area->classes[maquina.method_area->classes_count++] = _MCLASSL.load(_MUTIL.getClassPath(maquina.basePath, parentName));
        
        link(maquina.method_area->classes_count-1);
        initialize(maquina.method_area->classes_count-1);
        
        if (maquina.method_area->classes[maquina.method_area->classes_count-1]->super_class != 0) {
            flag = loadParentClasses(maquina);
        }
        
        // free(cl);
    }
    return flag;
}

/// carrega as interfaces da classe na posicao maquina.classes.size - 1 no array de interfaces da area de metodo
static int loadInterfaces(CLASS* class) {
    int interfacesCount = class->interfaces_count;
    
    for(int i=0; i<interfacesCount; i++){
        char* name = class->getInterfaceName(class, i);
        
        if (getInterfceIndex(name) == -1) {
            expandInterfaceArray();
            maquina.method_area->interfaces[maquina.method_area->interfaces_count++] = _MCLASSL.load(_MUTIL.getClassPath(maquina.basePath, name));
        }
        
    }
    
    // free(cl);
    return E_SUCCESS;
}


int loadClass(u1 *name) {
    
    if(name == NULL){
        return -1;
    }

    if (strchr(name, '$')) {
        error(E_DOLAR_NOT_SUPPORTED);
    }
    
    int toReturn = -1;
    if ((toReturn = getClassIndex(name)) <= -1) {
        
        toReturn = maquina.method_area->classes_count;
        expandClassArray();
        maquina.method_area->classes[maquina.method_area->classes_count++] =_MCLASSL.load(_MUTIL.getClassPath(maquina.basePath, name));
        
        link(maquina.method_area->classes_count-1);
        initialize(maquina.method_area->classes_count-1);
        
        loadParentClasses(); // insere em maquina.classes todas as classes pai ainda nao carregadas em maquina.clasess
        loadInterfaces(maquina.method_area->classes[toReturn]); // insere em maquinas.interfaces todas as interfaces ainda nao carregadas em maquina.interfaces
        
    }
    
    return toReturn;
}

u1 *getClassNameUtf8(ClassFile *pClass, u2 classIndexTemp) {
    u1 *bytes;
    u2 nameIndex;
    
    nameIndex = pFrame->pClass->constant_pool[classIndexTemp - 1].info.CONSTANT_Class_info.name_index;
    bytes = pCLass->constant_pool[nameIndex - 1].info.CONSTANT_Utf8_info.bytes;
    
    return bytes;
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



//
///**
// *  <#Description#>
// *
// *  @param pClass <#pClass description#>
// *  @param nIndex <#nIndex description#>
// *
// *  @return <#return value description#>
// */
u4 LoadConstant(ClassFile *pClass, u2 nIndex) {
    u4 v = 0;
    u1 *bytes;

    switch(pClass->constant_pool[nIndex - 1].tag)
    {
        case CONSTANT_INTEGER:
        case CONSTANT_FLOAT:
            v = pClass->constant_pool[nIndex -1].info.CONSTANT_IntegerFloat_info.bytes;
            break;
            
        case CONSTANT_STRING:
            bytes = pClass->constant_pool[pClass->constant_pool[nIndex - 1].info.CONSTANT_String_info.string_index - 1].info.CONSTANT_Utf8_info.bytes;
            v = bytes;

            break;
            
        case CONSTANT_DOUBLE:
            break;
            
        case CONSTANT_LONG:
            
            break;		
    }
    return v;
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
                

        
