//
//  Frame.c
//  
//
//  Created by Luiz Henrique Campos Barboza on 09/12/15.
//
//

#include "Frame.h"

/*!
	Empilha um valor na pilha de operandos
 */

void push(Frame *pFrame, u8 valor) {
    if (pFrame->operand_stack.allocated >= pFrame->max_stack) {
        error(E_STACK_OVERFLOW);
    }
    struct _u4pilha* ref = maquina.current_frame->operand_stack.topo; // armazena referencia ao antigo topo
    
    pFrame->operand_stack.topo = (struct _u4pilha*)malloc(sizeof(struct _u4pilha));
    pFrame->operand_stack.topo->next = ref; // guarda referencia para o proximo topo
    pFrame->operand_stack.topo->value = valor; // guarda o valor do topo
    pFrame->operand_stack.allocated++;
}

/*!
	desempilha um valor na pilha de operandos
 */
u8 pop(Frame *pFrame) {
    
    if (pFrame->operand_stack.topo == NULL || !pFrame->operand_stack.allocated) {
        error(E_EMPTY_STACK);
    }
    
    u8 toReturn = pFrame->operand_stack.topo->value; // guarda valor do topo
    pFrame->operand_stack.topo = pFrame->operand_stack.topo->next;
    pFrame->operand_stack.allocated--;
    
    return toReturn;
}
/*!
	empilha um valor na pilha de operandos
 */
void push2(Frame *pFrame, u8 valor) {
    push(pFrame, valor >> 32);
    push(pFrame, valor & 0xffffffff);
}

/*!
	desempilha um valor na pilha de operandos 64 bits
 */
u8 pop2(Frame *pFrame) {
    
    u8 var1,var2;
    u8 toReturn = 0;
    
    var1 = pop(pFrame);
    var2 = pop(pFrame);
    
    toReturn = var2;
    toReturn <<= 32;
    toReturn += var1;
    
    return toReturn;
}

/*!
	incicia e alococa um frame na memoria
 */
Frame *initFrame(ClassFile *Class, method_info *method, u2 codeIndex) {
    Frame *pFrame = (Frame *) malloc(sizeof(Frame));
    
    pFrame->code_length = method->attribute[codeIndex].info.Code_attribute.code_length;
    pFrame->code = method->attribute[codeIndex].info.Code_attribute.code;
    
    pFrame->max_stack = method->attribute[codeIndex].info.Code_attribute.max_stack;
    
    pFrame->max_locals = method->attribute[codeIndex].info.Code_attribute.max_locals;
    pFrame->local = (u8*) malloc(method->attribute[codeIndex].info.Code_attribute.max_locals*sizeof(u8));
    
    pFrame->operand_stack.allocated = 0;
    pFrame->operand_stack.topo = NULL;
    
    pFrame->pClass = Class;
    pFrame->pMethod = method;
    pFrame->pc = 0;
    pFrame->retornou = 0;
    
    return pFrame;
}