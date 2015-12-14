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
