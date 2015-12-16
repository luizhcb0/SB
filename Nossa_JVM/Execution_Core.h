//
//  Execution_Core.h
//  
//
//  Created by Luiz Henrique Campos Barboza on 09/12/15.
//
//

#ifndef Execution_Core_h
#define Execution_Core_h

#include "macros.h"
#include "Frame.h"

typedef struct _instruction {
    uint16_t qtd_operandos;
    char *nome;
    void (*call)(Frame*);
} Instruction;

extern const Instruction instructions[];
extern char *basePath;

typedef struct {
    ClassFile **classes;
    ClassFile **interfaces;
    u4 classes_count;
    u4 interfaces_count;
} MethodHeap;

MethodHeap initMethodHeap();

extern MethodHeap mHeap;


u1 * getFieldName(u2 index, cp_info *pool);
u4 LoadConstant(ClassFile *pClass, u2 nIndex);
Field_Value *getFieldValue(u1 *name, Field_Value *pField, u2 static_values_size);
u1 *GetStringFromConstPool(u2 nIndex, cp_info *pool);


#endif /* Execution_Core_h */
