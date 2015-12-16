//
//  instructions.c
//
//
//  Created by Luiz Henrique Campos Barboza on 13/12/15.
//
//

#include <stdio.h>
#include <inttypes.h>
#include "Heap.h"
#include "Exceptions.h"
#include "Execution_Core.h"
#include "JVM_core.h"

uint8_t wide = 0;
Heap objHeap;



/*!
	Incrementa PC
 */
static void func_op_nop(Frame *pFrame) {
    pFrame->pc++;
}

/*!
	Empilha NULL na pilha de operandos
 */
static void func_op_aconst_null(Frame *pFrame) {
    push(pFrame,0);
    pFrame->pc++;
}

/*!
	Empilha int -1 na pilha de operandos
 */
static void func_op_iconst_m1(Frame *pFrame) {
    push(pFrame,-1);
    pFrame->pc++;
}

/*!
	Empilha int 0 na pilha de operandos
 */
static void func_op_iconst_0(Frame *pFrame) {
    push(pFrame,0);
    pFrame->pc++;
}

/*!
	Empilha int 1 na pilha de operandos
 */
static void func_op_iconst_1(Frame *pFrame) {
    push(pFrame,1);
    pFrame->pc++;
}

/*!
	Empilha int 2 na pilha de operandos
 */
static void func_op_iconst_2(Frame *pFrame) {
    push(pFrame,2);
    pFrame->pc++;
}

/*!
	Empilha int 3 na pilha de operandos
 */
static void func_op_iconst_3(Frame *pFrame) {
    push(pFrame,3);
    pFrame->pc++;
}

/*!
	Empilha int 4 na pilha de operandos
 */
static void func_op_iconst_4(Frame *pFrame) {
    push(pFrame,4);
    pFrame->pc++;
}

/*!
	Empilha int 5 na pilha de operandos
 */
static void func_op_iconst_5(Frame *pFrame) {
    push(pFrame,5);
    pFrame->pc++;
}

/*!
	Empilha long 0 na pilha de operandos
 */
static void func_op_lconst_0(Frame *pFrame) {
    push2(pFrame,0);
    pFrame->pc++;
}

/*!
	Empilha long 1 na pilha de operandos
 */
static void func_op_lconst_1(Frame *pFrame) {
    push2(pFrame,1);
    pFrame->pc++;
}

/*!
	Empilha constante float 0.0 na pilha de operandos
 */
static void func_op_fconst_0(Frame *pFrame) {
    float float_number = 0.0;
    push(pFrame,*((u8*)&float_number));
    pFrame->pc++;
}

/*!
	Empilha constante float 1.0 na pilha de operandos
 */
static void func_op_fconst_1(Frame *pFrame) {
    float float_number = 1.0;
    push(pFrame,*((u8*)&float_number));
    pFrame->pc++;
}

/*!
	Empilha constante float 2.0 na pilha de operandos
 */
static void func_op_fconst_2(Frame *pFrame) {
    float float_number = 2.0;
    push(pFrame,*((u8*)&float_number));
    pFrame->pc++;
}

/*!
	Empilha constante double 0.0 na pilha de operandos
 */
static void func_op_dconst_0(Frame *pFrame) {
    double double_number = 0.0;
    u8 *aux_64 = malloc(sizeof(u8));

    memcpy(aux_64, &double_number, sizeof(u8));
    push2(pFrame,*aux_64);
    pFrame->pc++;
}

/*!
	Empilha constante double 1.0 na pilha de operandos
 */
static void func_op_dconst_1(Frame *pFrame) {
    double double_number = 1.0;
    u8 *aux_64 = malloc(sizeof(u8));

    memcpy(aux_64, &double_number, sizeof(u8));
    push2(pFrame,*aux_64);
    pFrame->pc++;
}

/*!
	Empilha um byte.
	O valor imediato do byte tem o sinal extendido para um valor int  (8 bits)
	O valor é colocado na pilha de operandos
 */
static void func_op_bipush(Frame *pFrame) {
    //Pula os 8 bits codigo da instrucao contida no array de codes
    int8_t var = 0;
    i8 aux;

    pFrame->pc++;
    var = pFrame->code[pFrame->pc];
    aux = (i8) var;
    push(pFrame,aux);

    pFrame->pc++;
}

static void func_op_sipush(Frame *pFrame) {
    uint8_t high,low;
    int16_t aux_16;
    //i8 t;

    pFrame->pc++;
    high = pFrame->code[pFrame->pc];
    pFrame->pc++;
    low = pFrame->code[pFrame->pc];

    aux_16 = high;
    aux_16 <<= 8;
    aux_16 |= low;

    push(pFrame,aux_16);
    pFrame->pc++;
}



static void func_op_ldc(Frame *pFrame) {
    uint8_t index, type;

    pFrame->pc++;
    index = pFrame->code[pFrame->pc];
    type = pFrame->pClass->constant_pool[index - 1].tag;

    switch (type) {
        case CONSTANT_INTEGER:
            push(pFrame,(i8)pFrame->pClass->constant_pool[index - 1].info.CONSTANT_IntegerFloat_info.bytes);
            break;
        case CONSTANT_FLOAT:
            push(pFrame,pFrame->pClass->constant_pool[index - 1].info.CONSTANT_IntegerFloat_info.bytes);
            break;
        case CONSTANT_STRING:
            push(pFrame,pFrame->pClass->constant_pool[index - 1].info.CONSTANT_String_info.string_index);
            break;

        default:
            break;
    }
    pFrame->pc++;

}

static void func_op_ldc_w(Frame *pFrame) {
    uint64_t index;
    uint8_t type;
    uint64_t high, low;

    pFrame->pc++;

    high = pFrame->code[pFrame->pc];
    pFrame->pc++;
    low = pFrame->code[pFrame->pc];

    index = high;
    index = index << 8;
    index = index | low;

    type = pFrame->pClass->constant_pool[index - 1].tag;

    switch (type) {
        case CONSTANT_INTEGER:
            push(pFrame,(i8)pFrame->pClass->constant_pool[index - 1].info.CONSTANT_IntegerFloat_info.bytes);
            break;
        case CONSTANT_FLOAT:
            push(pFrame,(i8)pFrame->pClass->constant_pool[index - 1].info.CONSTANT_IntegerFloat_info.bytes);
            break;
        case CONSTANT_STRING:
            push(pFrame,pFrame->pClass->constant_pool[index - 1].info.CONSTANT_String_info.string_index);
            break;

        default:
            break;
    }
    pFrame->pc++;
}

static void func_op_ldc2_w(Frame *pFrame) {

    uint64_t index, high, low, completeValue = 0;
    uint8_t type;

    high = pFrame->code[++pFrame->pc];
    low = pFrame->code[++pFrame->pc];

    index = high;
    index = index << 8;
    index = index | low;

    type = pFrame->pClass->constant_pool[index - 1].tag;

    switch (type) {
        case CONSTANT_LONG:
            high = pFrame->pClass->constant_pool[index - 1].info.CONSTANT_LongDouble_info.high_bytes;
            low = pFrame->pClass->constant_pool[index - 1].info.CONSTANT_LongDouble_info.low_bytes;
            long l = getLong(high, low);
            memcpy(&completeValue, &l, sizeof(u8));

            push2(pFrame,completeValue);
            break;
        case CONSTANT_DOUBLE:
            high = pFrame->pClass->constant_pool[index - 1].info.CONSTANT_LongDouble_info.high_bytes;
            low = pFrame->pClass->constant_pool[index - 1].info.CONSTANT_LongDouble_info.low_bytes;

            double d = getDouble(high, low);

            memcpy(&completeValue, &d, sizeof(u8));

            push2(pFrame,completeValue);
            break;
        default:
            break;
    }
    pFrame->pc++;
}


static void func_op_iload(Frame *pFrame) {

    uint16_t index;
    pFrame->pc++;
    index =  pFrame->code[pFrame->pc];

    if(wide == 1){
        index = index << 8;
        pFrame->pc++;
        index = index | pFrame->code[pFrame->pc];
        wide = 0;
    }

    push(pFrame,pFrame->local[index]);
    pFrame->pc++;
}

static void func_op_lload(Frame *pFrame) {
    uint16_t index;
    pFrame->pc++;
    index = pFrame->code[pFrame->pc];

    if(wide == 1){
        index = index << 8;
        pFrame->pc++;
        index = index | pFrame->code[pFrame->pc];
        wide = 0;
    }

    push(pFrame,pFrame->local[index]);
    push(pFrame,pFrame->local[index + 1]);

    pFrame->pc++;

}
static void func_op_fload(Frame *pFrame) {
    func_op_iload(pFrame);
}

static void func_op_dload(Frame *pFrame) {
    func_op_lload(pFrame);
}

static void func_op_aload(Frame *pFrame) {
    func_op_iload(pFrame);
}

static void func_op_iload_0(Frame *pFrame) {
    push(pFrame,pFrame->local[0]);
    pFrame->pc++;
}

static void func_op_iload_1(Frame *pFrame) {
    push(pFrame,pFrame->local[1]);
    pFrame->pc++;
}

static void func_op_iload_2(Frame *pFrame) {
    push(pFrame,pFrame->local[2]);
    pFrame->pc++;
}

static void func_op_iload_3(Frame *pFrame) {
    push(pFrame,pFrame->local[3]);
    pFrame->pc++;
}

static void func_op_lload_0(Frame *pFrame) {
    push(pFrame,pFrame->local[0]);
    push(pFrame,pFrame->local[1]);
    pFrame->pc++;
}

static void func_op_lload_1(Frame *pFrame) {
    push(pFrame,pFrame->local[1]);
    push(pFrame,pFrame->local[2]);
    pFrame->pc++;
}

static void func_op_lload_2(Frame *pFrame) {
    push(pFrame,pFrame->local[2]);
    push(pFrame,pFrame->local[3]);
    pFrame->pc++;
}

static void func_op_lload_3(Frame *pFrame) {
    push(pFrame,pFrame->local[3]);
    push(pFrame,pFrame->local[4]);
    pFrame->pc++;
}

static void func_op_fload_0(Frame *pFrame) {
    func_op_iload_0(pFrame);
}

static void func_op_fload_1(Frame *pFrame) {
    func_op_iload_1(pFrame);
}

static void func_op_fload_2(Frame *pFrame) {
    func_op_iload_2(pFrame);
}

static void func_op_fload_3(Frame *pFrame) {
    func_op_iload_3(pFrame);
}

static void func_op_dload_0(Frame *pFrame) {
    func_op_lload_0(pFrame);
}

static void func_op_dload_1(Frame *pFrame) {
    func_op_lload_1(pFrame);
}

static void func_op_dload_2(Frame *pFrame) {
    func_op_lload_2(pFrame);
}

static void func_op_dload_3(Frame *pFrame) {
    func_op_lload_3(pFrame);
}

static void func_op_aload_0(Frame *pFrame) {
    func_op_iload_0(pFrame);
}

static void func_op_aload_1(Frame *pFrame) {
    func_op_iload_1(pFrame);
}

static void func_op_aload_2(Frame *pFrame) {
    func_op_iload_2(pFrame);
}

static void func_op_aload_3(Frame *pFrame) {
    func_op_iload_3(pFrame);
}

static void func_op_iaload(Frame *pFrame) {
    u8 index, aux;
    struct _array *arrayRef;

    index = pop(pFrame);
    aux = pop(pFrame);
    memcpy(&arrayRef, &aux, sizeof(u8));

    push(pFrame,((uint32_t*)arrayRef->values)[index]);

    pFrame->pc++;
}

static void func_op_laload(Frame *pFrame) {
    u8 index, aux;
    struct _array *arrayRef;

    index = pop(pFrame);
    aux = pop(pFrame);
    memcpy(&arrayRef, &aux, sizeof(u8)); // convert to pointer

    //printf("\nlaload: index: %llx, aux: %llx, arrayRef: %p, values: %p\n", index, aux, arrayRef, arrayRef->values);
    push2(pFrame,((u8*)arrayRef->values)[index]);
    pFrame->pc++;
}

static void func_op_faload(Frame *pFrame) {
    u8 index, aux;
    struct _array* arrayRef;

    index = pop(pFrame);
    aux = pop(pFrame);
    memcpy(&arrayRef, &aux, sizeof(u8)); // convert to pointer

    push(pFrame,((uint32_t*)arrayRef->values)[index]);
    pFrame->pc++;
}

static void func_op_daload(Frame *pFrame) {
    u8 index, aux;
    struct _array *arrayRef;

    index = pop(pFrame);
    aux = pop(pFrame);
    memcpy(&arrayRef, &aux, sizeof(u8)); // convert to pointer

    push2(pFrame,((u8*)arrayRef->values)[index]);
    pFrame->pc++;
}

static void func_op_aaload(Frame *pFrame) {
    u8 index, aux;
    struct _array *arrayRef;

    index = pop(pFrame);
    aux = pop(pFrame);
    memcpy(&arrayRef, &aux, sizeof(u8));

    push(pFrame,((u8*)arrayRef->values)[index]);

    pFrame->pc++;
}

static void func_op_baload(Frame *pFrame) {
    u8 index,aux;
    struct _array* arrayRef;

    index = pop(pFrame);
    aux = pop(pFrame);
    memcpy(&arrayRef, &aux, sizeof(u8));

    push(pFrame,((int8_t*)arrayRef->values)[index]);
    pFrame->pc++;

}

static void func_op_caload(Frame *pFrame) {
    u8 index,aux;
    struct _array* arrayRef;

    index = pop(pFrame);
    aux = pop(pFrame);
    memcpy(&arrayRef, &aux, sizeof(u8));

    push(pFrame,((uint16_t*)arrayRef->values)[index]);
    pFrame->pc++;
}

static void func_op_saload(Frame *pFrame) {
    u8 index,aux;
    i8 t;
    struct _array* arrayRef;

    index = pop(pFrame);
    aux = pop(pFrame);
    memcpy(&arrayRef, &aux, sizeof(u8));

    t = ((int16_t*)arrayRef->values)[index];
    push(pFrame,t);
    pFrame->pc++;
}

static void func_op_istore(Frame *pFrame) {
    uint16_t index;
    i8 value;

    pFrame->pc++;

    index = pFrame->code[pFrame->pc];
    value = (i8)pop(pFrame);

    pFrame->local[index] = value;
    pFrame->pc++;
}

static void func_op_lstore(Frame *pFrame) {
    uint16_t index;
    u8 high, low;

    pFrame->pc++;

    index = pFrame->code[pFrame->pc];
    low = pop(pFrame);
    high = pop(pFrame);

    pFrame->local[index] = high;
    pFrame->local[index+1] = low;

    pFrame->pc++;
}

static void func_op_fstore(Frame *pFrame) {
    func_op_istore(pFrame);
}

static void func_op_dstore(Frame *pFrame) {
    uint16_t index;
    u8 high, low;

    pFrame->pc++;

    index = pFrame->code[pFrame->pc];
    low = pop(pFrame);
    high = pop(pFrame);

    pFrame->local[index] = high;
    pFrame->local[index+1] = low;

    pFrame->pc++;
}

static void func_op_astore(Frame *pFrame) {
    func_op_istore(pFrame);
}

static void func_op_istore_0(Frame *pFrame) {
    u8 value = pop(pFrame);

    pFrame->local[0] = value;
    pFrame->pc++;
}

static void func_op_istore_1(Frame *pFrame) {
    i8 value = pop(pFrame);

    pFrame->local[1] = value;
    pFrame->pc++;
}

static void func_op_istore_2(Frame *pFrame) {
    u8 value = pop(pFrame);

    pFrame->local[2] = value;
    pFrame->pc++;
}

static void func_op_istore_3(Frame *pFrame) {
    u8 value = pop(pFrame);

    pFrame->local[3] = value;
    pFrame->pc++;
}

static void func_op_lstore_0(Frame *pFrame) {
    u8 high, low;

    low = pop(pFrame);
    high = pop(pFrame);

    pFrame->local[0] = high;
    pFrame->local[1] = low;
    pFrame->pc++;
}

static void func_op_lstore_1(Frame *pFrame) {
    u8 high, low;

    low = pop(pFrame);
    high = pop(pFrame);

    pFrame->local[1]= high;
    pFrame->local[2] = low;
    pFrame->pc++;
}

static void func_op_lstore_2(Frame *pFrame) {
    u8 high, low;

    low = pop(pFrame);
    high = pop(pFrame);

    pFrame->local[2] = high;
    pFrame->local[3] = low;
    pFrame->pc++;
}

static void func_op_lstore_3(Frame *pFrame) {
    u8 high, low;

    low = pop(pFrame);
    high = pop(pFrame);

    pFrame->local[3]= high;
    pFrame->local[4] = low;
    pFrame->pc++;
}

static void func_op_fstore_0(Frame *pFrame) {
    u8  value;

    value = pop(pFrame);

    pFrame->local[0] = value;
    pFrame->pc++;
}

static void func_op_fstore_1(Frame *pFrame) {
    func_op_istore_1(pFrame);
}


static void func_op_fstore_2(Frame *pFrame) {
    func_op_istore_2(pFrame);
}

static void func_op_fstore_3(Frame *pFrame) {
    func_op_istore_3(pFrame);
}

static void func_op_dstore_0(Frame *pFrame) {
    func_op_lstore_0(pFrame);
}

static void func_op_dstore_1(Frame *pFrame) {
    func_op_lstore_1(pFrame);
}

static void func_op_dstore_2(Frame *pFrame) {
    func_op_lstore_2(pFrame);
}

static void func_op_dstore_3(Frame *pFrame) {
    func_op_lstore_3(pFrame);
}

static void func_op_astore_0(Frame *pFrame) {
    u8 value = pop(pFrame);

    pFrame->local[0] = value;
    pFrame->pc++;
}

static void func_op_astore_1(Frame *pFrame) {
    u8 value = pop(pFrame);

    pFrame->local[1] = value;
    pFrame->pc++;
}

static void func_op_astore_2(Frame *pFrame) {
    u8 value = pop(pFrame);

    pFrame->local[2] = value;
    pFrame->pc++;
}

static void func_op_astore_3(Frame *pFrame) {
    u8 value = pop(pFrame);

    pFrame->local[3] = value;
    pFrame->pc++;
}

static void func_op_iastore(Frame *pFrame) {
    u8 index, value, aux;
    struct _array* arrayRef;

    value = pop(pFrame);
    index = pop(pFrame);
    aux = pop(pFrame);

    memcpy(&arrayRef, &aux, sizeof(u8));

    ((uint32_t*)arrayRef->values)[index] = value;
    pFrame->pc++;
}


static void func_op_lastore(Frame *pFrame) {
    u8 index, low, high, aux;
    long value;
    struct _array* arrayRef;


    low = pop(pFrame);
    high = pop(pFrame);
    value = getLong(high, low);

    index = pop(pFrame);
    aux = pop(pFrame);
    memcpy(&arrayRef, &aux, sizeof(u8));

    ((u8*)arrayRef->values)[index] = value;
    pFrame->pc++;
}

static void func_op_fastore(Frame *pFrame) {
    u8 index, value, aux;
    struct _array* arrayRef;

    value = pop(pFrame);
    index = pop(pFrame);
    aux = pop(pFrame);

    memcpy(&arrayRef, &aux, sizeof(u8));

    ((uint32_t*)arrayRef->values)[index] = value;
    pFrame->pc++;
}

static void func_op_dastore(Frame *pFrame) {
    u8 index, low, high, aux,value;
    struct _array* arrayRef;


    low = pop(pFrame);
    high = pop(pFrame);

    value = high;
    value <<= 32;
    value += low;

    index = pop(pFrame);
    aux = pop(pFrame);
    memcpy(&arrayRef, &aux, sizeof(u8));

    ((u8*)arrayRef->values)[index] = value;
    pFrame->pc++;
}

static void func_op_aastore(Frame *pFrame) {
    u8 index,aux,value;
    struct _array* arrayRef;

    value = pop(pFrame);
    index = pop(pFrame);
    aux = pop(pFrame);
    memcpy(&arrayRef, &aux, sizeof(u8));

    ((u8*)arrayRef->values)[index] = value;
    pFrame->pc++;
}

static void func_op_bastore(Frame *pFrame) {
    u8 index,aux;
    uint8_t value;
    struct _array* arrayRef;

    value = pop(pFrame);
    index = pop(pFrame);
    aux = pop(pFrame);
    memcpy(&arrayRef, &aux, sizeof(u8));

    ((uint8_t*)arrayRef->values)[index] = (uint8_t)value;

    pFrame->pc++;
}

static void func_op_castore(Frame *pFrame) {
    u8 index,aux, value;
    struct _array* arrayRef;

    value = pop(pFrame);
    index = pop(pFrame);
    aux = pop(pFrame);
    memcpy(&arrayRef, &aux, sizeof(u8));

    ((uint16_t*)arrayRef->values)[index] = value;

    pFrame->pc++;
}

static void func_op_sastore(Frame *pFrame) {
    u8 index,aux;
    i8 value;
    struct _array* arrayRef;

    value = pop(pFrame);
    index = pop(pFrame);
    aux = pop(pFrame);
    memcpy(&arrayRef, &aux, sizeof(u8));

    ((int16_t*)arrayRef->values)[index] = (int16_t)value;

    pFrame->pc++;
}

static void func_op_pop(Frame *pFrame) {
    pop(pFrame);
    pFrame->pc++;
}

static void func_op_pop2(Frame *pFrame) {
    pop(pFrame);
    pop(pFrame);
    pFrame->pc++;
}

static void func_op_dup(Frame *pFrame) {
    u8 data;
    data = pop(pFrame);
    push(pFrame,data);
    push(pFrame,data);
    pFrame->pc++;
}

static void func_op_dup_x1(Frame *pFrame) {
    u8 data,other;
    data = pop(pFrame);
    other = pop(pFrame);
    push(pFrame,data);
    push(pFrame,other);
    push(pFrame,data);
    pFrame->pc++;
}

static void func_op_dup_x2(Frame *pFrame) {
    u8 data,other,last;
    data = pop(pFrame);
    other = pop(pFrame);
    last = pop(pFrame);
    push(pFrame,data);
    push(pFrame,last);
    push(pFrame,other);
    push(pFrame,data);
    pFrame->pc++;
}

static void func_op_dup2 (Frame *pFrame) {
    u8 data,other;
    data = pop(pFrame);
    other = pop(pFrame);
    push(pFrame,other);
    push(pFrame,data);
    push(pFrame,other);
    push(pFrame,data);
    pFrame->pc++;
}

static void func_op_dup2_x1(Frame *pFrame) {
    u8 data,other,last;
    data = pop(pFrame);
    other = pop(pFrame);
    last = pop(pFrame);
    push(pFrame,other);
    push(pFrame,data);
    push(pFrame,last);
    push(pFrame,other);
    push(pFrame,data);
    pFrame->pc++;
}

static void func_op_dup2_x2(Frame *pFrame) {
    u8 data,other,middle,last;
    data = pop(pFrame);
    other = pop(pFrame);
    middle = pop(pFrame);
    last = pop(pFrame);
    push(pFrame,other);
    push(pFrame,data);
    push(pFrame,last);
    push(pFrame,middle);
    push(pFrame,other);
    push(pFrame,data);
    pFrame->pc++;
}

static void func_op_swap(Frame *pFrame) {
    u8 data,other;
    data = pop(pFrame);
    other = pop(pFrame);
    push(pFrame,data);
    push(pFrame,other);
    pFrame->pc++;
}

static void func_op_iadd(Frame *pFrame) {
    u8 op,opp;
    op  = pop(pFrame);
    opp = pop(pFrame);

    push(pFrame,op+opp);
    pFrame->pc++;

}

static void func_op_ladd(Frame *pFrame) {

    u8 op,opp;
    u8 high,low;

    low  = pop(pFrame);
    high = pop(pFrame);

    op = high;
    op = op << 32;
    op = op + low;

    low  = pop(pFrame);
    high = pop(pFrame);

    opp = high;
    opp = opp << 32;
    opp = opp + low;

    push2(pFrame,op+opp);
    pFrame->pc++;

}

static void func_op_fadd(Frame *pFrame) {

    float op, opp, sum;
    u8 value, other,result;

    value = pop(pFrame);
    memcpy(&op, &value, sizeof(uint32_t));

    other = pop(pFrame);
    memcpy(&opp, &other, sizeof(uint32_t));

    sum = op + opp;

    memcpy(&result, &sum, sizeof(uint32_t));
    push(pFrame,result);

    pFrame->pc++;
}

static void func_op_dadd(Frame *pFrame) {

    u8 hiOp,loOp,hiOpp,loOpp;
    double sum;
    u8 completeValue = 0;

    loOp = pop(pFrame);
    hiOp = pop(pFrame);
    loOpp = pop(pFrame);
    hiOpp = pop(pFrame);

    sum = getDouble(hiOp,loOp) + getDouble(hiOpp,loOpp);
    memcpy(&completeValue, &sum, sizeof(u8));

    push2(pFrame,completeValue);

    pFrame->pc++;
}

static void func_op_isub(Frame *pFrame) {
    u8 op,opp;
    op  = pop(pFrame);
    opp = pop(pFrame);
    push(pFrame,opp-op);
    pFrame->pc++;
}

static void func_op_lsub(Frame *pFrame) {
    u8 op,opp;
    u8 high,low;

    low  = pop(pFrame);
    high = pop(pFrame);

    op = high;
    op = op << 32;
    op = op + low;

    low  = pop(pFrame);
    high = pop(pFrame);

    opp = high;
    opp = opp << 32;
    opp = opp + low;

    push2(pFrame,opp-op);
    pFrame->pc++;
}

static void func_op_fsub(Frame *pFrame) {
    float op, opp, sum;
    u8 value, other,result;

    value = pop(pFrame);
    memcpy(&op, &value, sizeof(uint32_t));

    other = pop(pFrame);
    memcpy(&opp, &other, sizeof(uint32_t));

    sum = opp - op;

    memcpy(&result, &sum, sizeof(uint32_t));
    push(pFrame,result);

    pFrame->pc++;
}

static void func_op_dsub(Frame *pFrame) {
    double op, opp, sum;
    u8 result;
    u8 high,low;

    low  = pop(pFrame);
    high = pop(pFrame);
    op = getDouble(high,low);

    low  = pop(pFrame);
    high = pop(pFrame);
    opp = getDouble(high,low);

    sum = opp - op;

    memcpy(&result, &sum, sizeof(u8));
    push2(pFrame,result);

    pFrame->pc++;
}

static void func_op_imul(Frame *pFrame) {
    u8 op,opp;
    op  = (i8)pop(pFrame);
    opp = (i8)pop(pFrame);
    push(pFrame,op*opp);
    pFrame->pc++;
}

static void func_op_lmul(Frame *pFrame) {

    i8 hop, lop, hopp, lopp;
    i8 op, opp;

    lop  = pop(pFrame);
    hop  = pop(pFrame);
    lopp = pop(pFrame);
    hopp = pop(pFrame);

    op  = hop;
    op  = op << 32;
    op  = op + lop;

    opp  = hopp;
    opp  = opp << 32;
    opp  = opp + lopp;

    push2(pFrame,(i8)(op*opp));
    pFrame->pc++;

}

static void func_op_fmul(Frame *pFrame) {
    float op, opp, mult;
    u8 value, other,result;

    value = pop(pFrame);
    memcpy(&op, &value, sizeof(uint32_t));

    other = pop(pFrame);
    memcpy(&opp, &other, sizeof(uint32_t));

    mult = op * opp;

    memcpy(&result, &mult, sizeof(uint32_t));
    push(pFrame,result);

    pFrame->pc++;
}

static void func_op_dmul(Frame *pFrame) {
    i8 hop, lop, hopp, lopp;
    double op, opp, mult;
    u8 final;

    lop  = pop(pFrame);
    hop  = pop(pFrame);
    lopp = pop(pFrame);
    hopp = pop(pFrame);

    op  = getDouble(hop,lop);
    opp  = getDouble(hopp,lopp);
    mult = op*opp;

    memcpy(&final, &mult, sizeof(i8));
    push2(pFrame,(final));

    pFrame->pc++;
}

static void func_op_idiv(Frame *pFrame) {
    u8 op,opp;
    op  = (i8)pop(pFrame);
    opp = (i8)pop(pFrame);
    push(pFrame,opp/op);
    pFrame->pc++;
}

static void func_op_ldiv(Frame *pFrame) {

    i8 hop, lop, hopp, lopp;
    i8 op, opp;

    lop  = pop(pFrame);
    hop  = pop(pFrame);
    lopp = pop(pFrame);
    hopp = pop(pFrame);

    op  = hop;
    op  = op << 32;
    op  = op + lop;

    opp  = hopp;
    opp  = opp << 32;
    opp  = opp + lopp;

    push2(pFrame,(i8)(opp/op));

    pFrame->pc++;
}

static void func_op_fdiv(Frame *pFrame) {
    float op, opp, mult;
    u8 value, other,result;

    value = pop(pFrame);
    memcpy(&op, &value, sizeof(uint32_t));

    other = pop(pFrame);
    memcpy(&opp, &other, sizeof(uint32_t));

    mult = opp/op;

    memcpy(&result, &mult, sizeof(uint32_t));
    push(pFrame,(u8)(result));

    pFrame->pc++;
}

static void func_op_ddiv(Frame *pFrame) {
    i8 hop, lop, hopp, lopp, final;
    double op, opp, div;

    lop  = pop(pFrame);
    hop  = pop(pFrame);
    lopp = pop(pFrame);
    hopp = pop(pFrame);

    op  = getDouble(hop,lop);
    opp  = getDouble(hopp,lopp);
    div = opp/op;

    memcpy(&final, &div, sizeof(i8));
    push2(pFrame,final);

    pFrame->pc++;
}

static void func_op_irem(Frame *pFrame) {
    u8 op,opp;
    op  = pop(pFrame);
    opp = pop(pFrame);
    push(pFrame,opp%op);
    pFrame->pc++;
}

static void func_op_lrem(Frame *pFrame) {
    u8 op,opp;
    u8 high,low;

    low  = pop(pFrame);
    high = pop(pFrame);

    op = high;
    op = op << 32;
    op = op + low;

    low  = pop(pFrame);
    high = pop(pFrame);

    opp = high;
    opp = opp << 32;
    opp = opp + low;

    push2(pFrame,opp%op);
    pFrame->pc++;
}

static void func_op_frem(Frame *pFrame) {
    float op, opp, mod;
    u8 value2, value1, result;

    value2 = pop(pFrame);
    memcpy(&op, &value2, sizeof(uint32_t));

    value1 = pop(pFrame);
    memcpy(&opp, &value1, sizeof(uint32_t));

    mod = fmodf(opp , op);
    memcpy(&result, &mod, sizeof(uint32_t));

    push(pFrame,result);
    pFrame->pc++;

}

static void func_op_drem(Frame *pFrame) {
    u8 hop, lop, hopp, lopp;
    double op, opp, mod;
    u8 final;

    lop  = pop(pFrame);
    hop  = pop(pFrame);
    lopp = pop(pFrame);
    hopp = pop(pFrame);

    op  = getDouble(hop,lop);
    opp  = getDouble(hopp,lopp);
    mod = fmod(opp,op);

    memcpy(&final, &mod, sizeof(u8));

    push2(pFrame,final);
    pFrame->pc++;
}

static void func_op_ineg(Frame *pFrame) {
    i8 op;
    u8 aux = 0;

    op  = -pop(pFrame);
    memcpy(&aux, &op, sizeof(u8));
    push(pFrame,aux);

    pFrame->pc++;
}

static void func_op_lneg(Frame *pFrame) {
    u8 op;
    u8 high,low;

    low  = pop(pFrame);
    high = pop(pFrame);

    op = high;
    op = op << 32;
    op = op + low;

    op = -(op);

    push2(pFrame,op);
    pFrame->pc++;
}

static void func_op_fneg(Frame *pFrame) {
    float op, negative;
    u8 value, result;

    value = pop(pFrame);
    memcpy(&op, &value, sizeof(uint32_t));

    negative = -op;

    memcpy(&result, &negative, sizeof(uint32_t));
    push(pFrame,result);

    pFrame->pc++;
}

static void func_op_dneg(Frame *pFrame) {
    double op, negative;
    u8 result;
    u8 high,low;

    low  = pop(pFrame);
    high = pop(pFrame);
    op = getDouble(high,low);

    negative = -op;

    memcpy(&result, &negative, sizeof(u8));
    push2(pFrame,result);

    pFrame->pc++;
}

static void func_op_ishl(Frame *pFrame) {
    u8 lowsFive = 0x1f;
    u8 value1, value2;

    value2 = pop(pFrame);
    value2 = value2 & lowsFive;

    value1 = pop(pFrame);
    value1 = value1 << value2;

    push(pFrame,value1);

    pFrame->pc++;
}

static void func_op_lshl(Frame *pFrame) {
    i8 bigBits;
    u8 lowSix = 0x3f;
    u8 low, high, result;

    result = pop(pFrame);
    result = result & lowSix;


    low = pop(pFrame);
    high = pop(pFrame);



    bigBits = high;
    bigBits = bigBits << 32;
    bigBits = (signed)(bigBits + low);
    bigBits = bigBits << result;

    push2(pFrame,bigBits);

    pFrame->pc++;
}

static void func_op_ishr(Frame *pFrame) {

    int32_t value1,lowFive = 0x1f;
    int32_t value2;

    value1 = pop(pFrame);
    value1 = value1 & lowFive;
    value2 = (signed)(int32_t)pop(pFrame);

    for(int j = 0; j < value1; j++) {
        value2 = value2 / 2;
    }

    push(pFrame,(i8)value2);
    pFrame->pc++;
}

static void func_op_lshr(Frame *pFrame) {

    u8 allOne = 0xffffffffffffffff, firstOne = 0x8000000000000000, var;
    u8 low, high, vartwo, lowSeven = 0x3f;;

    vartwo = pop(pFrame);
    vartwo = vartwo & lowSeven;

    allOne = allOne << (64-vartwo);
    low = pop(pFrame);
    high = pop(pFrame);


    var = high;
    var = var << 32;
    var = (signed)(var + low);

    firstOne = var & firstOne;
    var = var >> vartwo;

    if(firstOne == 1) {
        var = var | allOne;
    }

    push2(pFrame,(u8)var);

    pFrame->pc++;
}

static void func_op_iushr(Frame *pFrame) {
    u8 lowFive = 0x1f;
    u8 value, other;

    other = pop(pFrame);
    other = other & lowFive;
    value = pop(pFrame);
    value = value >> other;
    push(pFrame,value);
    pFrame->pc++;
}

static void func_op_lushr(Frame *pFrame) {
    i8 bigBits;
    u8 var, low, high, lowFive = 0x3f;

    var = pop(pFrame);
    var = var & lowFive;

    low = pop(pFrame);
    high = pop(pFrame);

    bigBits = high;
    bigBits = bigBits << 32;
    bigBits = (signed)(bigBits + low);

    bigBits = bigBits >> var;
    push2(pFrame,(u8)bigBits);

    pFrame->pc++;
}

static void func_op_iand(Frame *pFrame) {
    u8 op,opp;
    op  = pop(pFrame);
    opp = pop(pFrame);
    push(pFrame,op&opp);
    pFrame->pc++;
}

static void func_op_land(Frame *pFrame) {

    u8 op,opp;
    u8 high,low;

    low  = pop(pFrame);
    high = pop(pFrame);

    op = high;
    op = op << 32;
    op = op + low;

    low  = pop(pFrame);
    high = pop(pFrame);

    opp = high;
    opp = opp << 32;
    opp = opp + low;

    push2(pFrame,op&opp);
    pFrame->pc++;
}

static void func_op_ior(Frame *pFrame) {
    u8 op,opp;
    op  = pop(pFrame);
    opp = pop(pFrame);
    push(pFrame,op|opp);
    pFrame->pc++;
}

static void func_op_lor(Frame *pFrame) {
    u8 op,opp;
    u8 high,low;

    low  = pop(pFrame);
    high = pop(pFrame);

    op = high;
    op = op << 32;
    op = op + low;

    low  = pop(pFrame);
    high = pop(pFrame);

    opp = high;
    opp = opp << 32;
    opp = opp + low;

    push2(pFrame,op|opp);
    pFrame->pc++;
}

static void func_op_ixor(Frame *pFrame) {
    u8 op,opp;
    op  = pop(pFrame);
    opp = pop(pFrame);
    push(pFrame,op^opp);
    pFrame->pc++;
}

static void func_op_lxor(Frame *pFrame) {
    u8 op,opp;
    u8 high,low;

    low  = pop(pFrame);
    high = pop(pFrame);

    op = high;
    op = op << 32;
    op = op + low;

    low  = pop(pFrame);
    high = pop(pFrame);

    opp = high;
    opp = opp << 32;
    opp = opp + low;

    push2(pFrame,op^opp);
    pFrame->pc++;
}

static void func_op_iinc(Frame *pFrame) {
    uint8_t field_index = pFrame->code[++(pFrame->pc)];
    u8 auxiliar = pFrame->local[field_index];
    uint8_t auxiliar2 = pFrame->code[++(pFrame->pc)];
    int8_t index = (int8_t) auxiliar;
    int8_t constant = (int8_t) auxiliar2;


    index += constant;
    pFrame->local[field_index] = (u8) index;
    pFrame->pc++;
}

static void func_op_i2l(Frame *pFrame) {
    u8 value1, value3, oneOne = 0x80000000;
    u8 bigBits,getHigh = 0xffffffff00000000;

    value1 = pop(pFrame);
    value3 = value1 & oneOne;
    bigBits = (i8) value1;

    if(value3 == 1) {
        bigBits = bigBits | getHigh;
    }

    push2(pFrame,bigBits);
    pFrame->pc++;
}

static void func_op_i2f(Frame *pFrame) {

    u8 value;
    u8 value2 = 0;

    float number;

    value = pop(pFrame);

    number = (float)value;

    memcpy(&value2, &number, sizeof(float));
    push(pFrame,value2);

    pFrame->pc++;
}

static void func_op_i2d(Frame *pFrame) {

    u8 value;
    u8 value2 = 0;

    double number;

    value = pop(pFrame);

    number = (double)value;

    memcpy(&value2, &number, sizeof(double));
    push2(pFrame,value2);

    pFrame->pc++;
}

static void func_op_l2i(Frame *pFrame) {
    u8 low;
    low = pop(pFrame);
    pop(pFrame);
    push(pFrame,low);

    pFrame->pc++;
}

static void func_op_l2f(Frame *pFrame) {
    u8 low, high, toPush;
    long val;
    float number;

    low = pop(pFrame);
    high = pop(pFrame);

    val = getLong(high, low);
    number = (float)val;
    memcpy(&toPush, &number, sizeof(uint32_t));

    push(pFrame,toPush);
    pFrame->pc++;
}


static void func_op_l2d(Frame *pFrame) {
    u8 low, high, toPush = 0;
    long val;
    double number;

    low = pop(pFrame);
    high = pop(pFrame);

    val = getLong(high, low);

    number = (double)val;
    memcpy(&toPush, &number, sizeof(u8));

    push2(pFrame,toPush);
    pFrame->pc++;
}

static void func_op_f2i(Frame *pFrame) {
    u8 value;
    float number;

    value = pop(pFrame);
    memcpy(&number, &value, sizeof(uint32_t));
    value = (u8) number;

    push(pFrame,value);

    pFrame->pc++;
}

static void func_op_f2l(Frame *pFrame) {

    u8 value;
    u8 other;
    float number;

    value = pop(pFrame);
    memcpy(&number, &value, sizeof(uint32_t));

    other = (u8) number;
    push2(pFrame,other);

    pFrame->pc++;
}

static void func_op_f2d(Frame *pFrame) {

    u8 value;
    u8 other;

    double double_number;
    float float_number;

    value = pop(pFrame);
    memcpy(&float_number, &value, sizeof(uint32_t));

    double_number = (double) float_number;
    memcpy(&other, &double_number, sizeof(u8));

    push2(pFrame,other);

    pFrame->pc++;
}

static void func_op_d2i(Frame *pFrame) {

    i8 hop, lop;
    double op;
    u8 final;
    i8 int_number;

    lop  = pop(pFrame);
    hop  = pop(pFrame);

    op  = getDouble(hop,lop);

    int_number = (i8)op;

    memcpy(&final, &int_number, sizeof(i8));

    push(pFrame,(final));

    pFrame->pc++;
}

static void func_op_d2l(Frame *pFrame) {

    i8 hop, lop;
    double op;
    u8 final;
    long long_number;

    lop  = pop(pFrame);
    hop  = pop(pFrame);

    op  = getDouble(hop,lop);

    long_number = (long)op;

    memcpy(&final, &long_number, sizeof(i8));

    push2(pFrame,(final));

    pFrame->pc++;

}

static void func_op_d2f(Frame *pFrame) {

    i8 hop, lop;
    double op;
    uint32_t final;
    float float_number;

    lop  = pop(pFrame);
    hop  = pop(pFrame);

    op  = getDouble(hop,lop);

    float_number = (float) op;

    memcpy(&final, &float_number, sizeof(int32_t));
    push(pFrame,(final));

    pFrame->pc++;
}

static void func_op_i2b(Frame *pFrame) {

    int8_t value;
    i8 other;

    value = (int8_t) pop(pFrame);
    other = (i8)value;
    push(pFrame,(i8)other);

    pFrame->pc++;
}

static void func_op_i2c(Frame *pFrame) {

    int16_t value;
    i8 other;

    value = (int16_t) pop(pFrame);
    other = (i8)value;
    push(pFrame,(i8)other);

    pFrame->pc++;
}

static void func_op_i2s(Frame *pFrame) {

    int16_t value;
    i8 other;

    value = (int16_t) pop(pFrame);
    other = (i8)value;

    push(pFrame,(u8)other);

    pFrame->pc++;
}

static void func_op_lcmp(Frame *pFrame) {

    i8 result;
    i8 low, high;
    i8 value, other;

    low = pop(pFrame);
    high = pop(pFrame);
    other = getLong(high, low);

    low = pop(pFrame);
    high = pop(pFrame);

    value = getLong(high, low);


    if(value == other) {
        result = 0;
    } else{
        if(value > other) {
            result = 1;
        } else {
            result = -1;
        }
    }

    push(pFrame,result);
    pFrame->pc++;
}

static void func_op_fcmpl(Frame *pFrame) {

    i8 empilha;
    u8 value;
    float op, opp;

    value = pop(pFrame);

    memcpy(&opp, &value, sizeof(uint32_t));
    value = pop(pFrame);

    memcpy(&op, &value, sizeof(uint32_t));

    if(op == opp) {
        empilha = 0;
    }else{

        if(op > opp) {
            empilha = 1;
        }else {
            empilha = -1;
        }
    }

    push(pFrame,(u8) empilha);
    pFrame->pc++;
}

static void func_op_fcmpg(Frame *pFrame) {

    float value, other;
    u8 auxiliar;

    i8 resultado;

    auxiliar = pop(pFrame);
    memcpy(&other, &auxiliar, sizeof(uint32_t));

    auxiliar = pop(pFrame);
    memcpy(&value, &auxiliar, sizeof(uint32_t));

    if(value == other) {
        resultado = 0;
    } else{
        if(value > other) {
            resultado = 1;
        }else {
            resultado = -1;
        }
    }

    push(pFrame,(u8) resultado);
    pFrame->pc++;
}

static void func_op_dcmpl(Frame *pFrame) {
    double double_number, double_number2;
    u8 low, high;
    i8 empilha;

    low = pop(pFrame);
    high = pop(pFrame);

    double_number2 = getDouble(high, low);

    low = pop(pFrame);
    high = pop(pFrame);

    double_number = getDouble(high, low);

    if(double_number == double_number2) {
        empilha = 0;
    } else{
        if(double_number > double_number2) {
            empilha = 1;
        }else {
            empilha = -1;
        }
    }

    push(pFrame,(u8) empilha);
    pFrame->pc++;
}

static void func_op_dcmpg(Frame *pFrame) {
    double double_number, double_number2;
    u8 low, high;
    i8 empilha;

    low = pop(pFrame);
    high = pop(pFrame);

    double_number2 = getDouble(high, low);

    low = pop(pFrame);
    high = pop(pFrame);

    double_number = getDouble(high, low);

    if(double_number == double_number2) {
        empilha = 0;
    } else{
        if(double_number > double_number2) {
            empilha = 1;
        }else {
            empilha = -1;
        }
    }

    push(pFrame,(u8) empilha);
    pFrame->pc++;

}

static void func_op_ifeq(Frame *pFrame) {

    uint8_t pathOne, pathTwo;
    int16_t desloc;
    i8 value;

    pathOne = pFrame->code[(pFrame->pc)+1];
    pathTwo = pFrame->code[(pFrame->pc)+2];

    value = (signed) pop(pFrame);
    if(value == 0) {

        desloc = pathOne;
        desloc = desloc << 8;
        desloc = desloc | pathTwo;

        pFrame->pc = pFrame->pc + desloc;

    } else {
        pFrame->pc = pFrame->pc + 3;
    }
}


static void func_op_ifne(Frame *pFrame) {

    uint8_t pathOne, pathTwo;
    int16_t desloc;
    i8 value;

    pathOne = pFrame->code[(pFrame->pc)+1];
    pathTwo = pFrame->code[(pFrame->pc)+2];

    value = (signed) pop(pFrame);
    if(value != 0) {

        desloc = pathOne;
        desloc = desloc << 8;
        desloc = desloc | pathTwo;

        pFrame->pc = pFrame->pc + desloc;

    } else {
        pFrame->pc = pFrame->pc + 3;
    }
}

static void func_op_iflt(Frame *pFrame) {

    uint8_t pathOne, pathTwo;
    int16_t desloc;
    i8 value;

    pathOne = pFrame->code[(pFrame->pc)+1];
    pathTwo = pFrame->code[(pFrame->pc)+2];

    value = (signed) pop(pFrame);
    if(value < 0) {

        desloc = pathOne;
        desloc = desloc << 8;
        desloc = desloc | pathTwo;

        pFrame->pc = pFrame->pc + desloc;

    } else {
        pFrame->pc = pFrame->pc + 3;
    }
}

static void func_op_ifge(Frame *pFrame) {

    uint8_t pathOne, pathTwo;
    int16_t desloc;
    i8 value;

    pathOne = pFrame->code[(pFrame->pc)+1];
    pathTwo = pFrame->code[(pFrame->pc)+2];

    value = (signed) pop(pFrame);
    if(value >= 0) {

        desloc = pathOne;
        desloc = desloc << 8;
        desloc = desloc | pathTwo;

        pFrame->pc = pFrame->pc + desloc;

    } else {
        pFrame->pc = pFrame->pc + 3;
    }

}

static void func_op_ifgt(Frame *pFrame) {

    uint8_t pathOne, pathTwo;
    int16_t desloc;
    i8 value;

    pathOne = pFrame->code[(pFrame->pc)+1];
    pathTwo = pFrame->code[(pFrame->pc)+2];

    value = (signed) pop(pFrame);
    if(value > 0) {

        desloc = pathOne;
        desloc = desloc << 8;
        desloc = desloc | pathTwo;

        pFrame->pc = pFrame->pc + desloc;

    } else {
        pFrame->pc = pFrame->pc + 3;
    }

}

static void func_op_ifle(Frame *pFrame) {

    uint8_t pathOne, pathTwo;
    uint16_t desloc;
    i8 value;

    pathOne = pFrame->code[(pFrame->pc)+1];
    pathTwo = pFrame->code[(pFrame->pc)+2];

    value = (signed) pop(pFrame);

    if(value <= 0) {
        desloc = pathOne;
        desloc = desloc << 8;
        desloc = desloc | pathTwo;

        pFrame->pc = pFrame->pc + desloc;

    } else {
        pFrame->pc = pFrame->pc + 3;
    }
}

static void func_op_if_icmpeq(Frame *pFrame) {

    int8_t pathOne, pathTwo;
    i8 value1, value2;
    int16_t desloc;

    pathOne = pFrame->code[(pFrame->pc)+1];
    pathTwo = pFrame->code[(pFrame->pc)+2];

    value2 = (signed) pop(pFrame);
    value1 = (signed) pop(pFrame);

    if(value1 == value2) {

        desloc = pathOne;
        desloc = desloc << 8;
        desloc = desloc | pathTwo;

        pFrame->pc = pFrame->pc + desloc;

    } else {
        pFrame->pc = pFrame->pc + 3;
    }

}

static void func_op_if_icmpne(Frame *pFrame) {

    int8_t pathOne, pathTwo;
    i8 value1, value2;
    int16_t desloc;

    pathOne = pFrame->code[(pFrame->pc)+1];
    pathTwo = pFrame->code[(pFrame->pc)+2];

    value2 = (signed) pop(pFrame);
    value1 = (signed) pop(pFrame);

    if(value1 != value2) {

        desloc = pathOne;
        desloc = desloc << 8;
        desloc = desloc | pathTwo;

        pFrame->pc = pFrame->pc + desloc;

    } else {
        pFrame->pc = pFrame->pc + 3;
    }

}

static void func_op_if_icmplt(Frame *pFrame) {

    int8_t pathOne, pathTwo;
    i8 value1, value2;
    int16_t desloc;

    pathOne = pFrame->code[(pFrame->pc)+1];
    pathTwo = pFrame->code[(pFrame->pc)+2];

    value2 = (signed) pop(pFrame);
    value1 = (signed) pop(pFrame);

    if(value1 < value2) {

        desloc = pathOne;
        desloc = desloc << 8;
        desloc = desloc | pathTwo;

        pFrame->pc = pFrame->pc + desloc;

    } else {
        pFrame->pc = pFrame->pc + 3;
    }

}

static void func_op_if_icmpge(Frame *pFrame) {

    int8_t pathOne, pathTwo;
    i8 value1, value2;
    int16_t desloc;

    pathOne = pFrame->code[(pFrame->pc)+1];
    pathTwo = pFrame->code[(pFrame->pc)+2];

    value2 = (signed) pop(pFrame);
    value1 = (signed) pop(pFrame);

    if(value1 >= value2) {

        desloc = pathOne;
        desloc = desloc << 8;
        desloc = desloc | pathTwo;

        pFrame->pc = pFrame->pc + desloc;

    } else {
        pFrame->pc = pFrame->pc + 3;
    }

}

static void func_op_if_icmpgt(Frame *pFrame) {

    int8_t pathOne, pathTwo;
    i8 value1, value2;
    int16_t desloc;

    pathOne = pFrame->code[(pFrame->pc)+1];
    pathTwo = pFrame->code[(pFrame->pc)+2];

    value2 = (signed) pop(pFrame);
    value1 = (signed) pop(pFrame);

    if(value1 > value2) {

        desloc = pathOne;
        desloc = desloc << 8;
        desloc = desloc | pathTwo;

        pFrame->pc = pFrame->pc + desloc;

    } else {
        pFrame->pc = pFrame->pc + 3;
    }

}

static void func_op_if_icmple(Frame *pFrame) {

    int8_t pathOne, pathTwo;
    i8 value1, value2;
    int16_t desloc;

    pathOne = pFrame->code[(pFrame->pc)+1];
    pathTwo = pFrame->code[(pFrame->pc)+2];

    value2 = (signed) pop(pFrame);
    value1 = (signed) pop(pFrame);

    if(value1 <= value2) {

        desloc = pathOne;
        desloc = desloc << 8;
        desloc = desloc | pathTwo;

        pFrame->pc = pFrame->pc + desloc;

    } else {
        pFrame->pc = pFrame->pc + 3;
    }

}

static void func_op_if_acmpeg(Frame *pFrame) {

    int8_t pathOne, pathTwo;
    i8 value1, value2;
    int16_t desloc;

    pathOne = pFrame->code[(pFrame->pc)+1];
    pathTwo = pFrame->code[(pFrame->pc)+2];

    value2 = (signed) pop(pFrame);
    value1 = (signed) pop(pFrame);

    if(value1 == value2) {

        desloc = pathOne;
        desloc = desloc << 8;
        desloc = desloc | pathTwo;

        pFrame->pc = pFrame->pc + desloc;

    } else {
        pFrame->pc = pFrame->pc + 3;
    }

}

static void func_op_if_acmpne(Frame *pFrame) {

    int8_t pathOne, pathTwo;
    i8 value1, value2;
    int16_t desloc;

    pathOne = pFrame->code[(pFrame->pc)+1];
    pathTwo = pFrame->code[(pFrame->pc)+2];

    value2 = (signed) pop(pFrame);
    value1 = (signed) pop(pFrame);

    if(value1 != value2) {

        desloc = pathOne;
        desloc = desloc << 8;
        desloc = desloc | pathTwo;

        pFrame->pc = pFrame->pc + desloc;

    } else {
        pFrame->pc = pFrame->pc + 3;
    }

}

static void func_op_goto(Frame *pFrame) {
    uint8_t pathOne, pathTwo;
    int16_t desloc;
    pathOne = pFrame->code[(pFrame->pc)+1];
    pathTwo = pFrame->code[(pFrame->pc)+2];

    desloc = pathOne;
    desloc = desloc << 8;
    desloc = desloc | pathTwo;

    pFrame->pc += desloc;
}

static void func_op_jsr(Frame *pFrame) {

    uint8_t pathOne, pathTwo;
    int16_t desloc;

    push(pFrame,(pFrame->pc) + 3);
    pathOne = pFrame->code[(pFrame->pc)+1];
    pathTwo = pFrame->code[(pFrame->pc)+2];

    desloc = pathOne;
    desloc = desloc << 8;
    desloc = desloc | pathTwo;

    pFrame->pc = pFrame->pc + desloc;

}

static void func_op_ret(Frame *pFrame) {

    int16_t index;
    pFrame->pc++;
    index = pFrame->code[pFrame->pc];

    if(wide == 1){
        index = index << 8;
        pFrame->pc++;
        index = index | pFrame->code[pFrame->pc];
        wide = 0;
    }
    pFrame->pc = pFrame->local[index];
}

static void func_op_tableswitch(Frame *pFrame) {

    int padrao, hi, lo, index, i ,j;
    int *tabelao;

    u8 locate,saltar, tableSize, desloc, bytes[5];

    index = pop(pFrame);
    locate = pFrame->pc;

    while((pFrame->pc + 1) % 4 != 0)
        pFrame->pc++;

    pFrame->pc++;

    for(i = 0; i < 4; i++)
        bytes[i] = (u8)pFrame->code[pFrame->pc++];

    padrao = ( (bytes[0] & 0xFF) << 24) |((bytes[1] & 0xFF) << 16) |((bytes[2] & 0xFF) << 8) |(bytes[3] & 0xFF);


    for(i = 0; i < 4; i++)
        bytes[i] = (u8)pFrame->code[pFrame->pc++];

    lo = ((bytes[0] & 0xFF) << 24) |((bytes[1] & 0xFF) << 16) |((bytes[2] & 0xFF) << 8) |(bytes[3] & 0xFF);

    for(i = 0; i < 4; i++)
        bytes[i] = (u8)pFrame->code[pFrame->pc++];

    hi = ((bytes[0] & 0xFF) << 24) |((bytes[1] & 0xFF) << 16) |((bytes[2] & 0xFF) << 8) |(bytes[3] & 0xFF);

    tableSize = (hi-lo) + 1;
    tabelao = calloc(sizeof(u8), tableSize);


    for(i = 0; i < tableSize; i++) 	{

        for(j = 0; j < 4; j++) 	{
            bytes[j] = (u8)pFrame->code[pFrame->pc++];
        }

        tabelao[i] = ((bytes[0] & 0xFF) << 24) |((bytes[1] & 0xFF) << 16) |((bytes[2] & 0xFF) << 8) |(bytes[3] & 0xFF);
    }

    if(index > hi || index < lo ) {

        saltar = locate + padrao;

    } else {

        desloc = tabelao[index - lo];

        saltar = locate + desloc;
    }

    pFrame->pc = saltar;

}


static void func_op_lookupswitch(Frame *pFrame) {

    int padrao, index, i ,j, pairs,found;
    u8 locate,saltar, bytes[5];
    int32_t *match, *offset;

    index = pop(pFrame);
    locate = pFrame->pc;

    while((pFrame->pc + 1) % 4 != 0)
        pFrame->pc++;

    pFrame->pc++;

    for(i = 0; i < 4; i++)
        bytes[i] = (u8)pFrame->code[pFrame->pc++];

    padrao = ( (bytes[0] & 0xFF) << 24) |((bytes[1] & 0xFF) << 16) |((bytes[2] & 0xFF) << 8) |(bytes[3] & 0xFF);


    for(i = 0; i < 4; i++)
        bytes[i] = (u8)pFrame->code[pFrame->pc++];

    pairs = ((bytes[0] & 0xFF) << 24) |((bytes[1] & 0xFF) << 16) |((bytes[2] & 0xFF) << 8) |(bytes[3] & 0xFF);


    match = calloc(sizeof(int32_t), pairs);
    offset = calloc(sizeof(int32_t), pairs);

    for(i = 0; i < pairs; i++) {

        for(j = 0; j < 4; j++) 	{
            bytes[j] = (u8)pFrame->code[pFrame->pc++];
        }

        match[i] = ((bytes[0] & 0xFF) << 24) |((bytes[1] & 0xFF) << 16) |((bytes[2] & 0xFF) << 8) | (bytes[3] & 0xFF);

        for(j = 0; j < 4; j++) 	{
            bytes[j] = (u8)pFrame->code[pFrame->pc++];
        }
        offset[i] = ((bytes[0] & 0xFF) << 24) | ((bytes[1] & 0xFF) << 16) |((bytes[2] & 0xFF) << 8) | (bytes[3] & 0xFF);
    }

    i = 0;
    found = 0;
    while((i < pairs) &&(!found)) {
        if(match[i] == index)
            found = 1;
        i++;
    }
    i--;

    if(found) {
        saltar = offset[i] + locate;
    } else {
        saltar = padrao + locate;
    }

    pFrame->pc = saltar;

}


static void func_op_ireturn(Frame *pFrame) {
    u8 aux = pop(pFrame);

    //Fazer do nosso jeito
    deleteFrame();
    pFrame->retornou = 1;

    if (pFrame) {
        push(pFrame,aux);
    }

}

static void func_op_lreturn(Frame *pFrame) {
    u8 low = pop(pFrame);
    u8 high = pop(pFrame);

    //Fazer do nosso jeito
    deleteFrame();
    pFrame->retornou = 1;

    if (pFrame) {
        push2(pFrame,getLong(high,low));
    }
}

static void func_op_freturn(Frame *pFrame) {
    func_op_ireturn(pFrame);
}

static void func_op_dreturn(Frame *pFrame) {
    u8 low = pop(pFrame);
    u8 high = pop(pFrame);

    //Fazer do nosso jeito
    deleteFrame();
    pFrame->retornou = 1;

    if (pFrame) {

        push(pFrame,high);
        push(pFrame,low);
    }

}

static void func_op_areturn(Frame *pFrame) {
    func_op_ireturn(pFrame);
}

static void func_op_return(Frame *pFrame) {
    pFrame->retornou = 1;
}

static void func_op_getstatic(Frame *pFrame) {
    uint8_t index_1, index_2;
    uint16_t index, nameTypeIndex;
    u8 classIndexTemp;
    int32_t classIndex, field_index;
    u8 valor;
    u1 *className, *name, *type;

    index_1 = (uint8_t) pFrame->code[++(pFrame->pc)];
    index_2 = (uint8_t) pFrame->code[++(pFrame->pc)];
    index = ((uint16_t)index_1 << 8) |(uint16_t)index_2;

    classIndex = pFrame->pClass->constant_pool[index-1].info.CONSTANT_FieldMethodIMethod_info.class_index;
    className = getUtf8String(pFrame->pClass->constant_pool, pFrame->pClass->constant_pool[classIndex-1].info.CONSTANT_Class_info.name_index);

    nameTypeIndex = pFrame->pClass->constant_pool[index-1].info.CONSTANT_FieldMethodIMethod_info.name_and_type_index;
    name = getUtf8String(pFrame->pClass->constant_pool, pFrame->pClass->constant_pool[nameTypeIndex-1].info.CONSTANT_NameAndType_info.name_index);
    type = getUtf8String(pFrame->pClass->constant_pool, pFrame->pClass->constant_pool[nameTypeIndex-1].info.CONSTANT_NameAndType_info.descriptor_index);


    while((field_index = getFieldIndex(className, name, strlen((char*)name), type, strlen((char*)type))) == -1) {
        className = getParentName(getClassByName(className));
    }

    classIndex = loadClass(className);

    if(field_index < 0){
        field_index = searchStaticFieldVal(classIndex,name,type);
    }

    valor = getStaticFieldVal(classIndex , field_index);

    if(type[0] == 'J' || type[0] == 'D') {
        push2(pFrame,valor);
    } else {
        push(pFrame,valor);
    }

    pFrame->pc++;
}

static void func_op_putstatic(Frame *pFrame) {
    uint8_t index_1, index_2;
    uint16_t index, nameTypeIndex;
    u8 classIndexTemp;
    int32_t classIndex, field_index;
    u8 valor,valor2;
    u1 *className, *name, *type;

    index_1 = (uint8_t) pFrame->code[++(pFrame->pc)];
    index_2 = (uint8_t) pFrame->code[++(pFrame->pc)];
    index = ((uint16_t)index_1 << 8) |(uint16_t)index_2;

    if (!index) error(E_NOTVALID_CP_INDEX);

    classIndexTemp = pFrame->pClass->constant_pool[index-1].info.CONSTANT_FieldMethodIMethod_info.class_index;
    className = getUtf8String(pFrame->pClass->constant_pool, pFrame->pClass->constant_pool[classIndexTemp-1].info.CONSTANT_Class_info.name_index);

    nameTypeIndex = pFrame->pClass->constant_pool[index-1].info.CONSTANT_FieldMethodIMethod_info.name_and_type_index;
    name = getUtf8String(pFrame->pClass->constant_pool, pFrame->pClass->constant_pool[nameTypeIndex-1].info.CONSTANT_NameAndType_info.name_index);
    type = getUtf8String(pFrame->pClass->constant_pool, pFrame->pClass->constant_pool[nameTypeIndex-1].info.CONSTANT_NameAndType_info.descriptor_index);

    while((field_index = getFieldIndex(className, name, strlen((char*)name), type, strlen((char*)type))) == -1) {
        className = getParentName(getClassByName(className));
    }

    classIndex = loadClass(className);

    if(type[0] == 'J' || type[0] == 'D') {
        valor  = pop(pFrame);
        valor2 = pop(pFrame);
        valor = valor | (valor2 << 32);
    } else {
        valor = pop(pFrame);
    }

    setStaticFieldVal(classIndex , field_index, valor);
    pFrame->pc++;
}


static void func_op_getfield(Frame *pFrame) {
    uint8_t low, high;
    u8 index;
    i8 classIndex, field_index, aux;
    uint16_t nameTypeIndex;
    u1 *className, *name, *type;
    struct _object *objeto = NULL;
    u8 aux2;

    high = pFrame->code[++(pFrame->pc)];
    low = pFrame->code[++(pFrame->pc)];

    index = high;
    index <<= 8;
    index = index | low;

    if (!index) error(E_NOTVALID_CP_INDEX);

    classIndex = pFrame->pClass->constant_pool[index-1].info.CONSTANT_FieldMethodIMethod_info.class_index;
    className = getUtf8String(pFrame->pClass->constant_pool, pFrame->pClass->constant_pool[classIndex-1].info.CONSTANT_Class_info.name_index);


    nameTypeIndex = pFrame->pClass->constant_pool[index-1].info.CONSTANT_FieldMethodIMethod_info.name_and_type_index;
    name = getUtf8String(pFrame->pClass->constant_pool, pFrame->pClass->constant_pool[nameTypeIndex-1].info.CONSTANT_NameAndType_info.name_index);
    type = getUtf8String(pFrame->pClass->constant_pool, pFrame->pClass->constant_pool[nameTypeIndex-1].info.CONSTANT_NameAndType_info.descriptor_index);


    while((field_index = getFieldIndex(className, name, strlen((char*)name), type, strlen((char*)type))) == -1) {
        className = getParentName(getClassByName(className));
    }

    aux = pop(pFrame);
    memcpy(&objeto, &aux, sizeof(u8));

    aux2 = getObjectField(objeto, field_index);

    if(type[0] == 'J' || type[0] == 'D') {
        push2(pFrame,aux2);
    } else {
        push(pFrame,aux2);
    }

    pFrame->pc++;
}

static void func_op_putfield(Frame *pFrame) {

    uint8_t low, high;
    u8 index,aux;
    i8 classIndex, field_index, val_1;
    uint16_t nameTypeIndex;
    u1 *className, *name, *type;
    struct _object *objeto = NULL;
    u8 valor,valor2;

    high = pFrame->code[++(pFrame->pc)];
    low = pFrame->code[++(pFrame->pc)];

    index = high;
    index <<= 8;
    index = index | low;

    if (!index) error(E_NOTVALID_CP_INDEX);

    classIndex = pFrame->pClass->constant_pool[index-1].info.CONSTANT_FieldMethodIMethod_info.class_index;
    className = getUtf8String(pFrame->pClass->constant_pool, pFrame->pClass->constant_pool[classIndex-1].info.CONSTANT_Class_info.name_index);

    nameTypeIndex = pFrame->pClass->constant_pool[index-1].info.CONSTANT_FieldMethodIMethod_info.name_and_type_index;
    name = getUtf8String(pFrame->pClass->constant_pool, pFrame->pClass->constant_pool[nameTypeIndex-1].info.CONSTANT_NameAndType_info.name_index);
    type = getUtf8String(pFrame->pClass->constant_pool, pFrame->pClass->constant_pool[nameTypeIndex-1].info.CONSTANT_NameAndType_info.descriptor_index);

    while((field_index = getFieldIndex(className, name, strlen((char*)name), type, strlen((char*)type))) == -1) {
        className = getParentName(getClassByName(className));
    }

    if(type[0] == 'J' || type[0] == 'D') {
        valor  = pop(pFrame);
        valor2 = pop(pFrame);
        valor = valor | (valor2 << 32);

        aux = pop(pFrame);
        memcpy(&objeto, &aux, sizeof(u8));
        setObjectField(objeto, field_index, valor);

    } else {
        val_1 = pop(pFrame);
        aux = pop(pFrame);

        memcpy(&objeto, &aux, sizeof(u8));
        setObjectField(objeto, field_index, val_1);
    }

    pFrame->pc++;
}

static void func_op_invokevirtual(Frame *pFrame) {
    u8 index = 0, valorHigh = 0, valorLow = 0, vU8 = 0, array_ref = 0;
    uint8_t low = 0, high = 0;
    i8 numParams = 0, i = 0, j = 0;
    i8 classIndex = 0, classIndexTemp = 0;
    uint16_t nameTypeIndex = 0, methodNameIndex = 0, methodDescriptorIndex = 0;
    u1 *className = NULL, *methodName = NULL, *methodDesc = NULL;
    u8 *fieldsTemp = NULL;
    float vfloat = 0;
    ClassFile *class = NULL;
    method_info  *method = NULL;

    high = pFrame->code[++(pFrame->pc)];
    low = pFrame->code[++(pFrame->pc)];

    index = high;
    index <<= 8;
    index = index | low;

    if (!index) error(E_NOTVALID_CP_INDEX);

    classIndexTemp = pFrame->pClass->constant_pool[index-1].info.CONSTANT_FieldMethodIMethod_info.class_index;
    className = getUtf8String(pFrame->pClass->constant_pool, pFrame->pClass->constant_pool[classIndexTemp-1].info.CONSTANT_Class_info.name_index);
    nameTypeIndex = pFrame->pClass->constant_pool[index-1].info.CONSTANT_FieldMethodIMethod_info.name_and_type_index;

    methodNameIndex = pFrame->pClass->constant_pool[nameTypeIndex - 1].info.CONSTANT_NameAndType_info.name_index;
    methodDescriptorIndex = pFrame->pClass->constant_pool[nameTypeIndex - 1].info.CONSTANT_NameAndType_info.descriptor_index;
    methodDesc = getUtf8String(pFrame->pClass->constant_pool, methodDescriptorIndex);
    methodName = getUtf8String(pFrame->pClass->constant_pool, methodNameIndex);

    if((strcmp((char*)className, "java/io/PrintStream") == 0) && ((strcmp((char*)methodName,"println") == 0) ||(strcmp(methodName,"print") == 0))){

        //Quando tem que imprimir long
        if(strstr((char*)methodDesc, "J") != NULL){
            valorLow = pop(pFrame);
            valorHigh = pop(pFrame);

            printf("%ld",(long)getLong(valorHigh,valorLow));

            //Quando tem que imprimir double
        } else if(strstr((char*)methodDesc, "D") != NULL) {
            valorLow = pop(pFrame);
            valorHigh = pop(pFrame);

            printf("%f", (double)getDouble(valorHigh,valorLow));

            //Quando tem que imprimir boolean
        } else if(strstr((char*)methodDesc, "Z") != NULL) {

            if(!pop(pFrame)) {
                printf("false");
            } else {
                printf("true");
            }

            //Quando tem que imprimir char
        } else if(strstr((char*)methodDesc, "C") != NULL) {

            //array
            if(strstr((char*)methodDesc, "[C") != NULL){
                array_ref = pop(pFrame);
                for(i = 0; i < objHeap.array_count; i++){
                    if(!memcmp(&objHeap.arrays[i], &array_ref, sizeof(u8)))
                        break;
                }
                for(j = 0; j < objHeap.array_count; j++){
                    printf("%"PRIi16,(i2)(array_ref +i));
                }
                //CHAR
            } else {
                printf("%c",(int16_t)pop(pFrame));
            }

            //Quando tem que imprimir inteiro
        }else if(strstr((char*)methodDesc, "I") != NULL) {
            printf("%d",(int)pop(pFrame));

            //Quando tem que imprimir float
        }else if(strstr((char*)methodDesc, "F") != NULL) {
            vU8 = pop(pFrame);
            memcpy(&vfloat, &vU8, sizeof(uint32_t));
            printf("%f", vfloat);

            //Quando tem que imprimir string
        }else if(strstr((char*)methodDesc, "Ljava/lang/String") != NULL) {
            vU8 = pop(pFrame);
            printf("%s",pFrame->pClass->constant_pool[vU8-1].info.CONSTANT_Utf8_info.bytes);

            //OBJECT
        }else if(strstr((char*)methodDesc, "Ljava/lang/Object") != NULL) {
            void* aux = NULL;
            vU8 = pop(pFrame);
            memcpy(&aux, &vU8, sizeof(u8));
            printf("%p",aux);
        }

        if(strcmp((char*)methodName,"println") == 0) {
            printf("\n");
        }

        pop(pFrame);
    } else {
        classIndex = loadClass(className);
        class = mHeap.classes[classIndex];

        while(class != NULL && (method = getMethodByNameDesc(class, pFrame->pClass, nameTypeIndex)) == NULL) {
            className = getParentName(class);
            classIndex = loadClass(className);
            class = mHeap.classes[classIndex];
        }

        if(class == NULL) {
            printf("Erro: Metodo nao encontrando.\n");
            exit(1);
        }

        numParams = getNumParameters(class, method);
        fieldsTemp = calloc(sizeof(u8),numParams+1);
        for(i = numParams; i > 0; i--) {
            fieldsTemp[i] = pop(pFrame);
        }

        if(((method->access_flags) & 0x0100) || strcmp("println", (char*)getUtf8String(class->constant_pool, method->name_index)) == 0) {
            pop(pFrame);

            // implementar aqui codigo para lidar com metodos nativos

        } else {
            u8 objectref = pop(pFrame);
            createFrame(method,class);
            for(i = numParams; i > 0; i--) {
                pFrame->local[i] = fieldsTemp[i];
            }
            pFrame->local[0] = objectref;
            Execute();
        }
    }

    pFrame->pc++;
}

static void func_op_invokespecial(Frame *pFrame) {
    u8 index, *fieldsTemp;;
    uint8_t low, high;
    i8 i, classIndex, classIndexTemp;
    uint16_t nameTypeIndex;
    u1 *className;
    ClassFile *class;
    method_info *method;
    int numParams;

    high = pFrame->code[++(pFrame->pc)];
    low = pFrame->code[++(pFrame->pc)];

    index = high;
    index <<= 8;
    index = index | low;

    if (!index) error(E_NOTVALID_CP_INDEX);

    classIndexTemp = pFrame->pClass->constant_pool[index-1].info.CONSTANT_FieldMethodIMethod_info.class_index;
    className = getUtf8String(pFrame->pClass->constant_pool, pFrame->pClass->constant_pool[classIndexTemp-1].info.CONSTANT_Class_info.name_index);

    nameTypeIndex = pFrame->pClass->constant_pool[index-1].info.CONSTANT_FieldMethodIMethod_info.name_and_type_index;

    classIndex = loadClass(className);
    class = mHeap.classes[classIndex];

    while(class != NULL && (method = getMethodByNameDesc(class, pFrame->pClass, nameTypeIndex)) == NULL) {
        className = getParentName(class);
        classIndex = loadClass(className);
        class = mHeap.classes[classIndex];
    }

    if(class == NULL) {
        printf("Metodo nao foi encontrando, veja.\n");
    }

    numParams = getNumParameters(class , method);


    fieldsTemp = calloc(sizeof(u8),numParams+1);
    for(i = numParams; i > 0; i--) {
        fieldsTemp[i] = pop(pFrame);
    }

    if((method->access_flags) & 0x0100) {
        pop(pFrame);

        // implementar aqui codigo para lidar com metodos nativos

    } else {
        u8 objectref = pop(pFrame);
        createFrame(method,class);

        for(i = numParams; i > 0; i--) {
            pFrame->local[i] = fieldsTemp[i];
        }

        pFrame->local[0] = objectref;
        Execute();
    }

    pFrame->pc++;

}

static void func_op_invokestatic(Frame *pFrame) {
    u8 index, *fieldsTemp;
    uint8_t low, high;
    i8 numParams, i, classIndex, classIndexTemp;
    uint16_t nameTypeIndex;
    u1 *className;
    ClassFile *class;
    method_info *method;

    high = pFrame->code[++(pFrame->pc)];
    low = pFrame->code[++(pFrame->pc)];

    index = high;
    index <<= 8;
    index = index | low;

    if (!index) {
        error(E_NOTVALID_CP_INDEX);
    }

    classIndexTemp = pFrame->pClass->constant_pool[index - 1].info.CONSTANT_FieldMethodIMethod_info.class_index;
    className = getUtf8String(pFrame->pClass->constant_pool, pFrame->pClass->constant_pool[classIndexTemp-1].info.CONSTANT_Class_info.name_index);
    nameTypeIndex = pFrame->pClass->constant_pool[index - 1].info.CONSTANT_FieldMethodIMethod_info.name_and_type_index;

    classIndex = loadClass(className);
    class = mHeap.classes[classIndex];

    method = getMethodByNameDesc(class, pFrame->pClass, nameTypeIndex);
    numParams = getNumParameters(class , method);
    fieldsTemp = calloc(sizeof(u8),numParams+1);
    for(i = numParams - 1; i >= 0; i--) {
        fieldsTemp[i] = pop(pFrame);
    }

    if((method->access_flags) & 0x0100) {

        // Não implementado

    } else {
        createFrame(method,class);
        for(i = numParams - 1; i >= 0; i--) {
            pFrame->local[i] = fieldsTemp[i];
        }
        Execute();
    }
    pFrame->pc++;
}

static void func_op_invokeinterface(Frame *pFrame) {
    u8 index, *fieldsTemp;
    uint8_t low, high, args_count;
    i8 classIndex, classIndexTemp, i;
    uint16_t nameTypeIndex;
    u1 *className;
    ClassFile *class;
    method_info *method;

    high = pFrame->code[++(pFrame->pc)];
    low = pFrame->code[++(pFrame->pc)];

    index = high;
    index <<= 8;
    index = index | low;

    if (!index) {
        error(E_NOTVALID_CP_INDEX);
    }

    args_count = pFrame->code[++(pFrame->pc)];
    pFrame->pc++;

    fieldsTemp = calloc(sizeof(u8),args_count+1);


    for(i = args_count; i > 0; i--) {
        fieldsTemp[i] = pop(pFrame);
    }

    classIndexTemp = pFrame->pClass->constant_pool[index - 1].info.CONSTANT_FieldMethodIMethod_info.class_index;
    className = getUtf8String(pFrame->pClass->constant_pool, pFrame->pClass->constant_pool[classIndexTemp-1].info.CONSTANT_Class_info.name_index);
    nameTypeIndex = pFrame->pClass->constant_pool[index - 1].info.CONSTANT_FieldMethodIMethod_info.name_and_type_index;

    classIndex = loadClass(className);
    class = mHeap.classes[classIndex];

    while(class != NULL && (method = getMethodByNameDesc(class, pFrame->pClass, nameTypeIndex)) == NULL) {
        className = getParentName(class);
        classIndex = loadClass(className);
        class = mHeap.classes[classIndex];
    }

    if(class == NULL) {
        printf("Metodo nao encontrado.\n");
    }

    u8 objectref = pop(pFrame);
    createFrame(method,class);
    for(i = args_count; i > 0; i--) {
        pFrame->local[i] = fieldsTemp[i];
    }
    pFrame->local[0] = objectref;
    Execute();
    pFrame->pc++;

}

static void func_op_new(Frame *pFrame) {
    // printf("\n\t\t\tentrou _new");
    u1 low, high;
    u8 index;
    u1 *className;
    i8 classIndex;

    ClassFile *pClass;
    struct _object *objeto;

    high = pFrame->code[++(pFrame->pc)];
    low = pFrame->code[++(pFrame->pc)];

    index = high;
    index <<= 8;
    index |= low;


    if (!index) {
        error(E_NOTVALID_CP_INDEX);
    }
    className = getClassNameUtf8(pFrame->pClass, index);

    classIndex = loadClass(className);

    pClass = mHeap.classes[classIndex];

    objeto = newObject(pClass);


    push(pFrame,(u8)(intptr_t)objeto);
    pFrame->pc++;
}

static void func_op_newarray(Frame *pFrame) {
    int count;
    uint8_t type;
    count = pop(pFrame);
    pFrame->pc++;

    type = pFrame->code[(pFrame->pc)];
    if (count < 0) error(E_NEG_ARR_SIZE);

    push(pFrame,(u8)(intptr_t) newArray(count,type));
    pFrame->pc++;
}

static void func_op_anewarray(Frame *pFrame) {
    int count = pop(pFrame);
    if (count < 0) error(E_NEG_ARR_SIZE);

    uint8_t index_byte1 = pFrame->code[++pFrame->pc];
    uint8_t index_byte2 = pFrame->code[++pFrame->pc];
    uint16_t index = index_byte1; index = index << 8 | index_byte2;

    u1 *className = getClassNameUtf8(pFrame->pClass, index);

    void *pointer = newRefArray(count,(char*)className);

    push(pFrame,(u8)(intptr_t)pointer);
    pFrame->pc++;
}

static void func_op_arraylength(Frame *pFrame) {
    u8 reference = pop(pFrame);
    if (reference == 0) error(E_NULL_POINTER);

    for(int i=0;i < objHeap.array_count; i++){

        // push somente a quantidade do array correto
        if(!memcmp(&objHeap.arrays[i], &reference, sizeof(struct _array*))) {
            push(pFrame,objHeap.arrays[i]->quantidade);
            pFrame->pc++;
            return;
        }
    }

    error(E_ARR_NOT_FOUND);
}

static void func_op_athrow(Frame *pFrame) {
    pFrame->pc++;
}

static void func_op_checkcast(Frame *pFrame) {
    struct _object *reference;
    uint16_t index;

    pFrame->pc++;
    index = pFrame->code[(pFrame->pc)];
    index = index << 8;
    pFrame->pc++;
    index = index | pFrame->code[(pFrame->pc)];

    reference = (struct _object *)(intptr_t)pop(pFrame);

    u1 *className1 = getClassNameUtf8(pFrame->pClass, pFrame->pClass->this_class);
    u1 *className2 = getClassNameUtf8(reference->class, index);

    if(reference == NULL) {
        printf("Erro: Null Reference\n");
    }
    if(strcmp((char*)className1, (char*)className2) == 0) {
        printf(" Erro: Wrong Typt Object\n");
    }
    push(pFrame,(u8)(intptr_t)reference);
    pFrame->pc++;

}

static void func_op_instanceof(Frame *pFrame) {

    struct _object *reference;
    uint16_t index;

    pFrame->pc++;
    index = pFrame->code[(pFrame->pc)];
    index = index << 8;
    pFrame->pc++;
    index = index | pFrame->code[(pFrame->pc)];
    reference = (struct _object *)(intptr_t)pop(pFrame);

    if(reference == NULL) {
        printf("Erro: Null Reference\n");
    }

    u1 *className1 = getClassNameUtf8(pFrame->pClass, pFrame->pClass->this_class);
    u1 *className2 = getClassNameUtf8(reference->class, index);

    if(strcmp((char*)className1, (char*)className2) == 0) {
        push(pFrame,1);
        pFrame->pc++;
        return;
    }
    push(pFrame,0);
    pFrame->pc++;
}

static void func_op_monitorenter(Frame *pFrame) {
    printf("monitorenter: Not supported instruction");
    exit(1);
}

static void func_op_monitorexit(Frame *pFrame) {
    printf("monitorexit: Not supported instruction");
    exit(1);
}

static void func_op_wide(Frame *pFrame) {
    wide = 1;
    pFrame->pc++;
}

static void func_op_multianewarray(Frame *pFrame) {
    // error(E_NOT_SUPPORTED_INSTRUCTION);
    uint16_t index = pFrame->code[++pFrame->pc];
    index = index << 8 | pFrame->code[++pFrame->pc];
    int dimensionCount = pFrame->code[++pFrame->pc];
    u1 *marrayInfo = getClassNameUtf8(pFrame->pClass, index);

    // multianewarray apenas para arrays de dimensão >= 2
    if (dimensionCount < 1 || marrayInfo == NULL || (marrayInfo[0] != '[' && marrayInfo[1] != '[')) {
        error(E_NOT_VALID_MARRAY_INFO);
    }

    int* qtdByDimension = (int*)malloc(dimensionCount * sizeof(int));

    for (int i = 0; i < dimensionCount; i++) {
        int aux = pop(pFrame);
        if (aux > 0) {
            qtdByDimension[i] = aux;
        }else {
            error(E_NEGATIVE_ARRAY_SIZE);
        }
    }

    uint32_t tipo = 0;
    switch(marrayInfo[dimensionCount]) {
        case 'L': // seta o tipo e carrega classe para method_area
            tipo = tREFERENCIA;
            u1 *className = (u1*) malloc(strlen((char*)marrayInfo)*sizeof(u1));
            for (int i = dimensionCount + 1; i < strlen((char*)marrayInfo); i++) {
                className[i - dimensionCount - 1] = marrayInfo[i];
                className[i - dimensionCount] = '\0';
            }
            loadClass(className);
            break;
        case 'Z':
            tipo = tBOOLEAN;
            break;
        case 'C':
            tipo = tCHAR;
            break;
        case 'F':
            tipo = tFLOAT;
            break;
        case 'D':
            tipo = tDOUBLE;
            break;
        case 'B':
            tipo = tBYTE;
            break;
        case 'S':
            tipo = tSHORT;
            break;
        case 'I':
            tipo = tINT;
            break;
        case 'J':
            tipo = tLONG;
            break;
        case '[':
            error(E_DISTINCT_MARRAY_DIMENSIONS);
            break;
        default:
            error(E_NOT_SUPPORTED_ARRAY_TYPE);
            break;
    }

    void *pointer = newMultiArray(0, dimensionCount, qtdByDimension, tipo);
    push(pFrame,(u8)(intptr_t)pointer);
    pFrame->pc++;
}

static void func_op_ifnull(Frame *pFrame) {
    uint8_t bb1, bb2;
    i8 auxiliar_32;
    u8 offset;

    bb1 = pFrame->code[(pFrame->pc)+1];
    bb2 = pFrame->code[(pFrame->pc)+2];
    auxiliar_32 = (signed) pop(pFrame);

    if(auxiliar_32 == 0) {
        u8 value;
        value = bb1;
        value <<= 8;
        value |= bb2;
        offset = value;
        pFrame->pc += offset;
    } else {
        pFrame->pc += 3;
    }

}

static void func_op_ifnonnull(Frame *pFrame) {
    uint8_t bb1, bb2;
    i8 auxiliar_32;
    int16_t offset;

    bb1 = pFrame->code[(pFrame->pc)+1];
    bb2 = pFrame->code[(pFrame->pc)+2];
    auxiliar_32 = (signed) pop(pFrame);

    if(auxiliar_32 != 0){
        u8 value;
        value = bb1;
        value <<= 8;
        value |= bb2;
        offset = value;
        pFrame->pc += offset;
    }else{
        pFrame->pc += 3;
    }

}

static void func_op_goto_w(Frame *pFrame) {
    u8 bb1, bb2, bb3, bb4;
    i8 offset;

    bb1 = pFrame->code[(pFrame->pc)+1];
    bb2 = pFrame->code[(pFrame->pc)+2];
    bb3 = pFrame->code[(pFrame->pc)+3];
    bb4 = pFrame->code[(pFrame->pc)+4];

    offset = (i8)(((bb1 & 0xFF)<<24) |((bb2 & 0xFF)<<16) |((bb3 & 0xFF)<<8) |(bb4));
    pFrame->pc += offset;
}

static void func_op_jsr_w(Frame *pFrame) {
    u8 bb1, bb2, bb3, bb4;
    i8 offset;

    push(pFrame,(pFrame->pc)+5);

    bb1 = pFrame->code[(pFrame->pc)+1];
    bb2 = pFrame->code[(pFrame->pc)+2];
    bb3 = pFrame->code[(pFrame->pc)+3];
    bb4 = pFrame->code[(pFrame->pc)+4];

    offset = (i8)(((bb1 & 0xFF)<<24) |((bb2 & 0xFF)<<16) |((bb3 & 0xFF)<<8) |(bb4));
    pFrame->pc += offset;
}


const Instruction instructions[] = {
    {0,     "nop", 				func_op_nop		},
    {0, 	"aconst_null", 		func_op_aconst_null},
    {0, 	"iconst_m1", 		func_op_iconst_m1	},
    {0, 	"iconst_0", 		func_op_iconst_0	},
    {0, 	"iconst_1",			func_op_iconst_1	},
    {0, 	"iconst_2",			func_op_iconst_2	},
    {0, 	"iconst_3",			func_op_iconst_3	},
    {0, 	"iconst_4",			func_op_iconst_4	},
    {0, 	"iconst_5",			func_op_iconst_5	},
    {0, 	"lconst_0",			func_op_lconst_0	},
    {0, 	"lconst_1",			func_op_lconst_1	},
    {0, 	"fconst_0",			func_op_fconst_0	},
    {0, 	"fconst_1",			func_op_fconst_1	},
    {0, 	"fconst_2",			func_op_fconst_2	},
    {0, 	"dconst_0",			func_op_dconst_0	},
    {0, 	"dconst_1",			func_op_dconst_1	},
    {1, 	"bipush",			func_op_bipush		},
    {2, 	"sipush",			func_op_sipush		},
    {1, 	"ldc",				func_op_ldc         },
    {2, 	"ldc_w",			func_op_ldc_w		},
    {2, 	"ldc2_w",			func_op_ldc2_w		},
    {1, 	"iload",			func_op_iload		},
    {1, 	"lload",			func_op_lload		},
    {1, 	"fload",			func_op_fload		},
    {1, 	"dload",			func_op_dload		},
    {1, 	"aload",			func_op_aload		},
    {0, 	"iload_0",			func_op_iload_0     },
    {0, 	"iload_1",			func_op_iload_1     },
    {0, 	"iload_2",			func_op_iload_2     },
    {0, 	"iload_3",			func_op_iload_3     },
    {0, 	"lload_0",			func_op_lload_0     },
    {0, 	"lload_1",			func_op_lload_1     },
    {0, 	"lload_2",			func_op_lload_2     },
    {0, 	"lload_3",			func_op_lload_3     },
    {0, 	"fload_0",			func_op_fload_0     },
    {0, 	"fload_1",			func_op_fload_1     },
    {0, 	"fload_2",			func_op_fload_2     },
    {0, 	"fload_3",			func_op_fload_3     },
    {0, 	"dload_0",			func_op_dload_0     },
    {0, 	"dload_1",			func_op_dload_1     },
    {0, 	"dload_2",			func_op_dload_2     },
    {0, 	"dload_3",			func_op_dload_3     },
    {0, 	"aload_0",			func_op_aload_0     },
    {0, 	"aload_1",			func_op_aload_1     },
    {0, 	"aload_2",			func_op_aload_2     },
    {0, 	"aload_3",			func_op_aload_3     },
    {0, 	"iaload",			func_op_iaload		},
    {0, 	"laload",			func_op_laload		},
    {0, 	"faload",			func_op_faload		},
    {0, 	"daload",			func_op_daload		},
    {0, 	"aaload",			func_op_aaload		},
    {0, 	"baload",			func_op_baload		},
    {0, 	"caload",			func_op_caload		},
    {0, 	"saload",			func_op_saload		},
    {1, 	"istore",			func_op_istore		},
    {1, 	"lstore",			func_op_lstore		},
    {1, 	"fstore",			func_op_fstore		},
    {1, 	"dstore",			func_op_dstore		},
    {1, 	"astore",			func_op_astore		},
    {0, 	"istore_0",			func_op_istore_0	},
    {0, 	"istore_1",			func_op_istore_1	},
    {0, 	"istore_2",			func_op_istore_2	},
    {0, 	"istore_3",			func_op_istore_3	},
    {0, 	"lstore_0",			func_op_lstore_0	},
    {0, 	"lstore_1",			func_op_lstore_1	},
    {0, 	"lstore_2",			func_op_lstore_2	},
    {0, 	"lstore_3",			func_op_lstore_3	},
    {0, 	"fstore_0",			func_op_fstore_0	},
    {0, 	"fstore_1",			func_op_fstore_1	},
    {0, 	"fstore_2",			func_op_fstore_2	},
    {0, 	"fstore_3",			func_op_fstore_3	},
    {0, 	"dstore_0",			func_op_dstore_0	},
    {0, 	"dstore_1",			func_op_dstore_1	},
    {0, 	"dstore_2",			func_op_dstore_2	},
    {0, 	"dstore_3",			func_op_dstore_3	},
    {0, 	"astore_0",			func_op_astore_0	},
    {0, 	"astore_1",			func_op_astore_1	},
    {0, 	"astore_2",			func_op_astore_2	},
    {0, 	"astore_3",			func_op_astore_3	},
    {0, 	"iastore",			func_op_iastore     },
    {0, 	"lastore",			func_op_lastore     },
    {0, 	"fastore",			func_op_fastore     },
    {0, 	"dastore",			func_op_dastore     },
    {0, 	"aastore",			func_op_aastore     },
    {0, 	"bastore",			func_op_bastore     },
    {0, 	"castore",			func_op_castore     },
    {0, 	"sastore",			func_op_sastore     },
    {0, 	"pop",				func_op_pop         },
    {0, 	"pop2",				func_op_pop2		},
    {0, 	"dup",				func_op_dup         },
    {0, 	"dup_x1",			func_op_dup_x1		},
    {0, 	"dup_x2",			func_op_dup_x2		},
    {0, 	"dup2",				func_op_dup2		},
    {0, 	"dup2_x1",			func_op_dup2_x1     },
    {0, 	"dup2_x2",			func_op_dup2_x2     },
    {0, 	"swap",				func_op_swap		},
    {0, 	"iadd",				func_op_iadd		},
    {0, 	"ladd",				func_op_ladd		},
    {0, 	"fadd",				func_op_fadd		},
    {0, 	"dadd",				func_op_dadd		},
    {0, 	"isub",				func_op_isub		},
    {0, 	"lsub",				func_op_lsub		},
    {0, 	"fsub",				func_op_fsub		},
    {0, 	"dsub",				func_op_dsub		},
    {0, 	"imul",				func_op_imul		},
    {0, 	"lmul",				func_op_lmul		},
    {0, 	"fmul",				func_op_fmul		},
    {0, 	"dmul",				func_op_dmul		},
    {0, 	"idiv",				func_op_idiv		},
    {0, 	"ldiv",				func_op_ldiv		},
    {0, 	"fdiv",				func_op_fdiv		},
    {0, 	"ddiv",				func_op_ddiv		},
    {0, 	"irem",				func_op_irem		},
    {0, 	"lrem",				func_op_lrem		},
    {0, 	"frem",				func_op_frem		},
    {0, 	"drem",				func_op_drem		},
    {0, 	"ineg",				func_op_ineg		},
    {0, 	"lneg",				func_op_lneg		},
    {0, 	"fneg",				func_op_fneg		},
    {0, 	"dneg",				func_op_dneg		},
    {0, 	"ishl",				func_op_ishl		},
    {0, 	"lshl",				func_op_lshl		},
    {0, 	"ishr",				func_op_ishr		},
    {0, 	"lshr",				func_op_lshr		},
    {0, 	"iushr",			func_op_iushr		},
    {0, 	"lushr",			func_op_lushr		},
    {0, 	"iand",				func_op_iand		},
    {0, 	"land",				func_op_land		},
    {0, 	"ior",				func_op_ior         },
    {0, 	"lor",				func_op_lor         },
    {0, 	"ixor",				func_op_ixor		},
    {0, 	"lxor",				func_op_lxor		},
    {2, 	"iinc",				func_op_iinc		},
    {0, 	"i2l",				func_op_i2l         },
    {0, 	"i2f",				func_op_i2f         },
    {0, 	"i2d",				func_op_i2d         },
    {0, 	"l2i",				func_op_l2i         },
    {0, 	"l2f",				func_op_l2f         },
    {0, 	"l2d",				func_op_l2d         },
    {0, 	"f2i",				func_op_f2i         },
    {0, 	"f2l",				func_op_f2l         },
    {0, 	"f2d",				func_op_f2d         },
    {0, 	"d2i",				func_op_d2i         },
    {0, 	"d2l",				func_op_d2l         },
    {0, 	"d2f",				func_op_d2f         },
    {0, 	"i2b",				func_op_i2b         },
    {0, 	"i2c",				func_op_i2c         },
    {0, 	"i2s",				func_op_i2s         },
    {0, 	"lcmp",				func_op_lcmp		},
    {0, 	"fcmpl",			func_op_fcmpl		},
    {0, 	"fcmpg",			func_op_fcmpg		},
    {0, 	"dcmpl",			func_op_dcmpl		},
    {0, 	"dcmpg",			func_op_dcmpg		},
    {2, 	"ifeq",				func_op_ifeq		},
    {2, 	"ifne",				func_op_ifne		},
    {2, 	"iflt",				func_op_iflt		},
    {2, 	"ifge",				func_op_ifge		},
    {2, 	"ifgt",				func_op_ifgt		},
    {2, 	"ifle",				func_op_ifle		},
    {2, 	"if_icmpeq",		func_op_if_icmpeq	},
    {2, 	"if_icmpne",		func_op_if_icmpne	},
    {2, 	"if_icmplt",		func_op_if_icmplt	},
    {2, 	"if_icmpge",		func_op_if_icmpge	},
    {2, 	"if_icmpgt",		func_op_if_icmpgt	},
    {2, 	"if_icmple",		func_op_if_icmple	},
    {2, 	"if_acmpeg",		func_op_if_acmpeg	},
    {2, 	"if_acmpne",		func_op_if_acmpne	},
    {2, 	"goto",				func_op_goto		},
    {2, 	"jsr",				func_op_jsr         },
    {1, 	"ret",				func_op_ret         },
    {14, 	"tableswitch",		func_op_tableswitch },
    {10,	"lookupswitch",		func_op_lookupswitch},
    {0, 	"ireturn",			func_op_ireturn     },
    {0, 	"lreturn",			func_op_lreturn     },
    {0, 	"freturn",			func_op_freturn     },
    {0, 	"dreturn",			func_op_dreturn     },
    {0, 	"areturn",			func_op_areturn     },
    {0, 	"return",			func_op_return		},
    {2, 	"getstatic",		func_op_getstatic	},
    {2, 	"putstatic",		func_op_putstatic	},
    {2, 	"getfield",			func_op_getfield	},
    {2, 	"putfield",			func_op_putfield	},
    {2, 	"invokevirtual",	func_op_invokevirtual},
    {2, 	"invokespecial",	func_op_invokespecial},
    {2, 	"invokestatic",		func_op_invokestatic},
    {4, 	"invokeinterface",	func_op_invokeinterface},
    {0, 	NULL,				NULL                },
    {2, 	"new",				func_op_new         },
    {1, 	"newarray",			func_op_newarray	},
    {2, 	"anewarray",		func_op_anewarray	},
    {0, 	"arraylength",		func_op_arraylength },
    {0, 	"athrow",			func_op_athrow		},
    {0, 	"checkcast",		func_op_checkcast	},
    {0, 	"instanceof",		func_op_instanceof	},
    {0, 	"monitorenter",		func_op_monitorenter},
    {0, 	"monitorexit",		func_op_monitorexit },
    {7, 	"wide",				func_op_wide		},
    {3, 	"multianewarray",	func_op_multianewarray},
    {2, 	"ifnull",			func_op_ifnull		},
    {2, 	"ifnonnull",		func_op_ifnonnull	},
    {4, 	"goto_w",			func_op_goto_w		},
    {4, 	"jsr_w",			func_op_jsr_w		}
};
