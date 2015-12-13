//
//  instructions.c
//  
//
//  Created by Luiz Henrique Campos Barboza on 13/12/15.
//
//

#include <stdio.h>
#include "maquina.h"

UTIL _MUTIL;
CLASS _MCLASS;
METHOD_POOL _MMETHODP;
ATTRIBUTE_POOL _MATTRIBUTEP;
CONSTANT_POOL _MCONSTANTP;
JVM maquina;

uint8_t WIDE = 0;

const Instruction_t instructions[] = {
    {0,     "nop", 				op_nop			},
    {0, 	"aconst_null", 		op_aconst_null	},
    {0, 	"iconst_m1", 		op_iconst_m1	},
    {0, 	"iconst_0", 		op_iconst_0		},
    {0, 	"iconst_1",			op_iconst_1		},
    {0, 	"iconst_2",			op_iconst_2		},
    {0, 	"iconst_3",			op_iconst_3		},
    {0, 	"iconst_4",			op_iconst_4		},
    {0, 	"iconst_5",			op_iconst_5		},
    {0, 	"lconst_0",			op_lconst_0		},
    {0, 	"lconst_1",			op_lconst_1		},
    {0, 	"fconst_0",			op_fconst_0		},
    {0, 	"fconst_1",			op_fconst_1		},
    {0, 	"fconst_2",			op_fconst_2		},
    {0, 	"dconst_0",			op_dconst_0		},
    {0, 	"dconst_1",			op_dconst_1		},
    {1, 	"bipush",			op_bipush		},
    {2, 	"sipush",			op_sipush		},
    {1, 	"ldc",				op_ldc			},
    {2, 	"ldc_w",			op_ldc_w		},
    {2, 	"ldc2_w",			op_ldc2_w		},
    {1, 	"iload",			op_iload		},
    {1, 	"lload",			op_lload		},
    {1, 	"fload",			op_fload		},
    {1, 	"dload",			op_dload		},
    {1, 	"aload",			op_aload		},
    {0, 	"iload_0",			op_iload_0		},
    {0, 	"iload_1",			op_iload_1		},
    {0, 	"iload_2",			op_iload_2		},
    {0, 	"iload_3",			op_iload_3		},
    {0, 	"lload_0",			op_lload_0		},
    {0, 	"lload_1",			op_lload_1		},
    {0, 	"lload_2",			op_lload_2		},
    {0, 	"lload_3",			op_lload_3		},
    {0, 	"fload_0",			op_fload_0		},
    {0, 	"fload_1",			op_fload_1		},
    {0, 	"fload_2",			op_fload_2		},
    {0, 	"fload_3",			op_fload_3		},
    {0, 	"dload_0",			op_dload_0		},
    {0, 	"dload_1",			op_dload_1		},
    {0, 	"dload_2",			op_dload_2		},
    {0, 	"dload_3",			op_dload_3		},
    {0, 	"aload_0",			op_aload_0		},
    {0, 	"aload_1",			op_aload_1		},
    {0, 	"aload_2",			op_aload_2		},
    {0, 	"aload_3",			op_aload_3		},
    {0, 	"iaload",			op_iaload		},
    {0, 	"laload",			op_laload		},
    {0, 	"faload",			op_faload		},
    {0, 	"daload",			op_daload		},
    {0, 	"aaload",			op_aaload		},
    {0, 	"baload",			op_baload		},
    {0, 	"caload",			op_caload		},
    {0, 	"saload",			op_saload		},
    {1, 	"istore",			op_istore		},
    {1, 	"lstore",			op_lstore		},
    {1, 	"fstore",			op_fstore		},
    {1, 	"dstore",			op_dstore		},
    {1, 	"astore",			op_astore		},
    {0, 	"istore_0",			op_istore_0		},
    {0, 	"istore_1",			op_istore_1		},
    {0, 	"istore_2",			op_istore_2		},
    {0, 	"istore_3",			op_istore_3		},
    {0, 	"lstore_0",			op_lstore_0		},
    {0, 	"lstore_1",			op_lstore_1		},
    {0, 	"lstore_2",			op_lstore_2		},
    {0, 	"lstore_3",			op_lstore_3		},
    {0, 	"fstore_0",			op_fstore_0		},
    {0, 	"fstore_1",			op_fstore_1		},
    {0, 	"fstore_2",			op_fstore_2		},
    {0, 	"fstore_3",			op_fstore_3		},
    {0, 	"dstore_0",			op_dstore_0		},
    {0, 	"dstore_1",			op_dstore_1		},
    {0, 	"dstore_2",			op_dstore_2		},
    {0, 	"dstore_3",			op_dstore_3		},
    {0, 	"astore_0",			op_astore_0		},
    {0, 	"astore_1",			op_astore_1		},
    {0, 	"astore_2",			op_astore_2		},
    {0, 	"astore_3",			op_astore_3		},
    {0, 	"iastore",			op_iastore		},
    {0, 	"lastore",			op_lastore		},
    {0, 	"fastore",			op_fastore		},
    {0, 	"dastore",			op_dastore		},
    {0, 	"aastore",			op_aastore		},
    {0, 	"bastore",			op_bastore		},
    {0, 	"castore",			op_castore		},
    {0, 	"sastore",			op_sastore		},
    {0, 	"pop",				op_pop			},
    {0, 	"pop2",				op_pop2			},
    {0, 	"dup",				op_dup			},
    {0, 	"dup_x1",			op_dup_x1		},
    {0, 	"dup_x2",			op_dup_x2		},
    {0, 	"dup2",				op_dup2			},
    {0, 	"dup2_x1",			op_dup2_x1		},
    {0, 	"dup2_x2",			op_dup2_x2		},
    {0, 	"swap",				op_swap			},
    {0, 	"iadd",				op_iadd			},
    {0, 	"ladd",				op_ladd			},
    {0, 	"fadd",				op_fadd			},
    {0, 	"dadd",				op_dadd			},
    {0, 	"isub",				op_isub			},
    {0, 	"lsub",				op_lsub			},
    {0, 	"fsub",				op_fsub			},
    {0, 	"dsub",				op_dsub			},
    {0, 	"imul",				op_imul			},
    {0, 	"lmul",				op_lmul			},
    {0, 	"fmul",				op_fmul			},
    {0, 	"dmul",				op_dmul			},
    {0, 	"idiv",				op_idiv			},
    {0, 	"ldiv",				op_ldiv			},
    {0, 	"fdiv",				op_fdiv			},
    {0, 	"ddiv",				op_ddiv			},
    {0, 	"irem",				op_irem			},
    {0, 	"lrem",				op_lrem			},
    {0, 	"frem",				op_frem			},
    {0, 	"drem",				op_drem			},
    {0, 	"ineg",				op_ineg			},
    {0, 	"lneg",				op_lneg			},
    {0, 	"fneg",				op_fneg			},
    {0, 	"dneg",				op_dneg			},
    {0, 	"ishl",				op_ishl			},
    {0, 	"lshl",				op_lshl			},
    {0, 	"ishr",				op_ishr			},
    {0, 	"lshr",				op_lshr			},
    {0, 	"iushr",			op_iushr		},
    {0, 	"lushr",			op_lushr		},
    {0, 	"iand",				op_iand			},
    {0, 	"land",				op_land			},
    {0, 	"ior",				op_ior			},
    {0, 	"lor",				op_lor			},
    {0, 	"ixor",				op_ixor			},
    {0, 	"lxor",				op_lxor			},
    {2, 	"iinc",				op_iinc			},
    {0, 	"i2l",				op_i2l			},
    {0, 	"i2f",				op_i2f			},
    {0, 	"i2d",				op_i2d			},
    {0, 	"l2i",				op_l2i			},
    {0, 	"l2f",				op_l2f			},
    {0, 	"l2d",				op_l2d			},
    {0, 	"f2i",				op_f2i			},
    {0, 	"f2l",				op_f2l			},
    {0, 	"f2d",				op_f2d			},
    {0, 	"d2i",				op_d2i			},
    {0, 	"d2l",				op_d2l			},
    {0, 	"d2f",				op_d2f			},
    {0, 	"i2b",				op_i2b			},
    {0, 	"i2c",				op_i2c			},
    {0, 	"i2s",				op_i2s			},
    {0, 	"lcmp",				op_lcmp			},
    {0, 	"fcmpl",			op_fcmpl		},
    {0, 	"fcmpg",			op_fcmpg		},
    {0, 	"dcmpl",			op_dcmpl		},
    {0, 	"dcmpg",			op_dcmpg		},
    {2, 	"ifeq",				op_ifeq			},
    {2, 	"ifne",				op_ifne			},
    {2, 	"iflt",				op_iflt			},
    {2, 	"ifge",				op_ifge			},
    {2, 	"ifgt",				op_ifgt			},
    {2, 	"ifle",				op_ifle			},
    {2, 	"if_icmpeq",		op_if_icmpeq	},
    {2, 	"if_icmpne",		op_if_icmpne	},
    {2, 	"if_icmplt",		op_if_icmplt	},
    {2, 	"if_icmpge",		op_if_icmpge	},
    {2, 	"if_icmpgt",		op_if_icmpgt	},
    {2, 	"if_icmple",		op_if_icmple	},
    {2, 	"if_acmpeg",		op_if_acmpeg	},
    {2, 	"if_acmpne",		op_if_acmpne	},
    {2, 	"goto",				op_goto			},
    {2, 	"jsr",				op_jsr			},
    {1, 	"ret",				op_ret			},
    {14, 	"tableswitch",		op_tableswitch	},
    {10,	"lookupswitch",		op_lookupswitch	},
    {0, 	"ireturn",			op_ireturn		},
    {0, 	"lreturn",			op_lreturn		},
    {0, 	"freturn",			op_freturn		},
    {0, 	"dreturn",			op_dreturn		},
    {0, 	"areturn",			op_areturn		},
    {0, 	"return",			op_return		},
    {2, 	"getstatic",		op_getstatic	},
    {2, 	"putstatic",		op_putstatic	},
    {2, 	"getfield",			op_getfield		},
    {2, 	"putfield",			op_putfield		},
    {2, 	"invokevirtual",	op_invokevirtual},
    {2, 	"invokespecial",	op_invokespecial},
    {2, 	"invokestatic",		op_invokestatic	},
    {4, 	"invokeinterface",	op_invokeinterface},
    {0, 	NULL,				NULL			},
    {2, 	"new",				op_new			},
    {1, 	"newarray",			op_newarray		},
    {2, 	"anewarray",		op_anewarray	},
    {0, 	"arraylength",		op_arraylength	},
    {0, 	"athrow",			op_athrow		},
    {0, 	"checkcast",		op_checkcast	},
    {0, 	"instanceof",		op_instanceof	},
    {0, 	"monitorenter",		op_monitorenter	},
    {0, 	"monitorexit",		op_monitorexit	},
    {7, 	"wide",				op_wide			},
    {3, 	"multianewarray",	op_multianewarray},
    {2, 	"ifnull",			op_ifnull		},
    {2, 	"ifnonnull",		op_ifnonnull	},
    {4, 	"goto_w",			op_goto_w		},
    {4, 	"jsr_w",			op_jsr_w		}
};


/*!
	Incrementa PC
 */
static void op_nop(Frame *pFrame) {
    pFrame->pc++;
}

/*!
	Empilha NULL na pilha de operandos
 */
static void op_aconst_null(Frame *pFrame) {
    pFrame->push(0);
    pFrame->pc++;
}

/*!
	Empilha int -1 na pilha de operandos
 */
static void op_iconst_m1(Frame *pFrame) {
    pFrame->push(-1);
    pFrame->pc++;
}

/*!
	Empilha int 0 na pilha de operandos
 */
static void op_iconst_0(Frame *pFrame) {
    pFrame->push(0);
    pFrame->pc++;
}

/*!
	Empilha int 1 na pilha de operandos
 */
static void op_iconst_1(Frame *pFrame) {
    pFrame->push(1);
    pFrame->pc++;
}

/*!
	Empilha int 2 na pilha de operandos
 */
static void op_iconst_2(Frame *pFrame) {
    pFrame->push(2);
    pFrame->pc++;
}

/*!
	Empilha int 3 na pilha de operandos
 */
static void op_iconst_3(Frame *pFrame) {
    pFrame->push(3);
    pFrame->pc++;
}

/*!
	Empilha int 4 na pilha de operandos
 */
static void op_iconst_4(Frame *pFrame) {
    pFrame->push(4);
    pFrame->pc++;
}

/*!
	Empilha int 5 na pilha de operandos
 */
static void op_iconst_5(Frame *pFrame) {
    pFrame->push(5);
    pFrame->pc++;
}

/*!
	Empilha long 0 na pilha de operandos
 */
static void op_lconst_0(Frame *pFrame) {
    pFrame->push2(0);
    pFrame->pc++;
}

/*!
	Empilha long 1 na pilha de operandos
 */
static void op_lconst_1(Frame *pFrame) {
    pFrame->push2(1);
    pFrame->pc++;
}

/*!
	Empilha constante float 0.0 na pilha de operandos
 */
static void op_fconst_0(Frame *pFrame) {
    float float_number = 0.0;
    pFrame->push(*((uint64_t*)&float_number));
    pFrame->pc++;
}

/*!
	Empilha constante float 1.0 na pilha de operandos
 */
static void op_fconst_1(Frame *pFrame) {
    float float_number = 1.0;
    pFrame->push(*((uint64_t*)&float_number));
    pFrame->pc++;
}

/*!
	Empilha constante float 2.0 na pilha de operandos
 */
static void op_fconst_2(Frame *pFrame) {
    float float_number = 2.0;
    pFrame->push(*((uint64_t*)&float_number));
    pFrame->pc++;
}

/*!
	Empilha constante double 0.0 na pilha de operandos
 */
static void op_dconst_0(Frame *pFrame) {
    double double_number = 0.0;
    uint64_t *aux_64 = malloc(sizeof(uint64_t));
    
    memcpy(aux_64, &double_number, sizeof(uint64_t));
    pFrame->push2(*aux_64);
    pFrame->pc++;
}

/*!
	Empilha constante double 1.0 na pilha de operandos
 */
static void op_dconst_1(Frame *pFrame) {
    double double_number = 1.0;
    uint64_t *aux_64 = malloc(sizeof(uint64_t));
    
    memcpy(aux_64, &double_number, sizeof(uint64_t));
    pFrame->push2(*aux_64);
    pFrame->pc++;
}

/*!
	Empilha um byte.
	O valor imediato do byte tem o sinal extendido para um valor int  (8 bits)
	O valor é colocado na pilha de operandos
 */
static void op_bipush(Frame *pFrame) {
    //Pula os 8 bits codigo da instrucao contida no array de codes
    int8_t var = 0;
    int64_t aux;
    
    pFrame->pc++;
    var = pFrame->code[pFrame->pc];
    aux = (int64_t) var;
    pFrame->push(aux);
    
    pFrame->pc++;
}

static void op_sipush(Frame *pFrame) {
    uint8_t high,low;
    int16_t aux_16;
    //int64_t t;
    
    pFrame->pc++;
    high = pFrame->code[pFrame->pc];
    pFrame->pc++;
    low = pFrame->code[pFrame->pc];
    
    aux_16 = high;
    aux_16 <<= 8;
    aux_16 |= low;
    
    pFrame->push(aux_16);
    pFrame->pc++;
}

static void op_ldc(Frame *pFrame) {
    uint8_t indice, type;
    
    maquina.current_frame->pc++;
    indice = maquina.current_frame->code_attr->code[maquina.current_frame->pc];
    type = maquina.current_frame->runtime_constant_pool->constants[indice-1].tag;
    
    if(type == tInteger){
        maquina.current_frame->push((int64_t)maquina.current_frame->runtime_constant_pool->constants[indice-1].type.Integer.bytes);
    }else if(type == tFloat){
        maquina.current_frame->push(maquina.current_frame->runtime_constant_pool->constants[indice-1].type.Float.bytes);
    }else if(type == tString){
        maquina.current_frame->push(maquina.current_frame->runtime_constant_pool->constants[indice-1].type.String.stringIndex);
    }
    
    maquina.current_frame->pc++;
    
}

static void op_ldc_w(Frame *pFrame) {
    uint64_t indice;
    uint8_t type;
    uint64_t high, low;
    
    maquina.current_frame->pc++;
    
    high = maquina.current_frame->code_attr->code[maquina.current_frame->pc];
    maquina.current_frame->pc++;
    low = maquina.current_frame->code_attr->code[maquina.current_frame->pc];
    
    indice = high;
    indice = indice << 8;
    indice = indice | low;
    
    type = maquina.current_frame->runtime_constant_pool->constants[indice-1].tag;
    
    if(type == tInteger){
        maquina.current_frame->push((int64_t)maquina.current_frame->runtime_constant_pool->constants[indice-1].type.Integer.bytes);
    }
    if(type == tFloat){
        maquina.current_frame->push(maquina.current_frame->runtime_constant_pool->constants[indice-1].type.Float.bytes);
    }
    else if(type == tString){
        maquina.current_frame->push(maquina.current_frame->runtime_constant_pool->constants[indice-1].type.String.stringIndex);
    }
    
    maquina.current_frame->pc++;
}

static void op_ldc2_w(Frame *pFrame) {
    
    uint64_t indice, high, low, completeValue = 0;
    uint8_t type;
    
    high = maquina.current_frame->code_attr->code[++maquina.current_frame->pc];
    low = maquina.current_frame->code_attr->code[++maquina.current_frame->pc];
    
    indice = high;
    indice = indice << 8;
    indice = indice | low;
    
    type = maquina.current_frame->runtime_constant_pool->constants[indice-1].tag;
    
    if(type == tLong){
        
        high = maquina.current_frame->runtime_constant_pool->constants[indice-1].type.Long.highBytes;
        low = maquina.current_frame->runtime_constant_pool->constants[indice-1].type.Long.lowBytes;
        long l = getLong(high, low);
        memcpy(&completeValue, &l, sizeof(uint64_t));
        
        maquina.current_frame->push2(completeValue);
        
        
    }else if(type == tDouble){
        
        high = maquina.current_frame->runtime_constant_pool->constants[indice-1].type.Double.highBytes;
        low = maquina.current_frame->runtime_constant_pool->constants[indice-1].type.Double.lowBytes;
        
        double d = getDouble(high, low);
        
        memcpy(&completeValue, &d, sizeof(uint64_t));
        
        maquina.current_frame->push2(completeValue);
    }
    
    maquina.current_frame->pc++;
}

static void op_iload(Frame *pFrame) {
    
    uint16_t indice;
    maquina.current_frame->pc++;
    indice =  maquina.current_frame->code_attr->code[maquina.current_frame->pc];
    
    if(WIDE == 1){
        indice = indice << 8;
        maquina.current_frame->pc++;
        indice = indice | maquina.current_frame->code_attr->code[maquina.current_frame->pc];
        WIDE = 0;
    }
    
    maquina.current_frame->push(maquina.current_frame->local_variables[indice]);
    maquina.current_frame->pc++;
}

static void op_lload(Frame *pFrame) {
    uint16_t indice;
    maquina.current_frame->pc++;
    indice = maquina.current_frame->code_attr->code[maquina.current_frame->pc];
    
    if(WIDE == 1){
        indice = indice << 8;
        maquina.current_frame->pc++;
        indice = indice | maquina.current_frame->code_attr->code[maquina.current_frame->pc];
        WIDE = 0;
    }
    
    maquina.current_frame->push(maquina.current_frame->local_variables[indice]);
    maquina.current_frame->push(maquina.current_frame->local_variables[indice+1]);
    
    
    maquina.current_frame->pc++;
    
}
static void op_fload(Frame *pFrame) {
    op_iload(pFrame);
}

static void op_dload(Frame *pFrame) {
    op_lload(pFrame);
}

static void op_aload(Frame *pFrame) {
    op_iload(pFrame);
}

static void op_iload_0(Frame *pFrame) {
    maquina.current_frame->push(maquina.current_frame->local_variables[0]);
    maquina.current_frame->pc++;
}

static void op_iload_1(Frame *pFrame) {
    maquina.current_frame->push(maquina.current_frame->local_variables[1]);
    maquina.current_frame->pc++;
}

static void op_iload_2(Frame *pFrame) {
    maquina.current_frame->push(maquina.current_frame->local_variables[2]);
    maquina.current_frame->pc++;
}

static void op_iload_3(Frame *pFrame) {
    maquina.current_frame->push(maquina.current_frame->local_variables[3]);
    maquina.current_frame->pc++;
}

static void op_lload_0(Frame *pFrame) {
    maquina.current_frame->push(maquina.current_frame->local_variables[0]);
    maquina.current_frame->push(maquina.current_frame->local_variables[1]);
    maquina.current_frame->pc++;
}

static void op_lload_1(Frame *pFrame) {
    maquina.current_frame->push(maquina.current_frame->local_variables[1]);
    maquina.current_frame->push(maquina.current_frame->local_variables[2]);
    maquina.current_frame->pc++;
}

static void op_lload_2(Frame *pFrame) {
    maquina.current_frame->push(maquina.current_frame->local_variables[2]);
    maquina.current_frame->push(maquina.current_frame->local_variables[3]);
    maquina.current_frame->pc++;
}

static void op_lload_3(Frame *pFrame) {
    maquina.current_frame->push(maquina.current_frame->local_variables[3]);
    maquina.current_frame->push(maquina.current_frame->local_variables[4]);
    maquina.current_frame->pc++;
}

static void op_fload_0(Frame *pFrame) {
    op_iload_0(pFrame);
}

static void op_fload_1(Frame *pFrame) {
    op_iload_1(pFrame);
}

static void op_fload_2(Frame *pFrame) {
    op_iload_2(pFrame);
}


static void op_fload_3(Frame *pFrame) {
    op_iload_3(pFrame);
}

static void op_dload_0(Frame *pFrame) {
    op_lload_0(pFrame);
}

static void op_dload_1(Frame *pFrame) {
    op_lload_1(pFrame);
}

static void op_dload_2(Frame *pFrame) {
    op_lload_2(pFrame);
}

static void op_dload_3(Frame *pFrame) {
    op_lload_3(pFrame);
}

static void op_aload_0(Frame *pFrame) {
    op_iload_0(pFrame);
}

static void op_aload_1(Frame *pFrame) {
    op_iload_1(pFrame);
}

static void op_aload_2(Frame *pFrame) {
    op_iload_2(pFrame);
}

static void op_aload_3(Frame *pFrame) {
    op_iload_3(pFrame);
}

static void op_iaload(Frame *pFrame) {
    uint64_t indice, aux;
    struct _array *arrayRef;
    
    indice = maquina.current_frame->pop();
    aux = maquina.current_frame->pop();
    memcpy(&arrayRef, &aux, sizeof(uint64_t));
    
    maquina.current_frame->push(((uint32_t*)arrayRef->values)[indice]);
    
    maquina.current_frame->pc++;
}

static void op_laload(Frame *pFrame) {
    uint64_t indice, aux;
    struct _array *arrayRef;
    
    indice = maquina.current_frame->pop();
    aux = maquina.current_frame->pop();
    memcpy(&arrayRef, &aux, sizeof(uint64_t)); // convert to pointer
    
    //printf("\nlaload: indice: %llx, aux: %llx, arrayRef: %p, values: %p\n", indice, aux, arrayRef, arrayRef->values);
    maquina.current_frame->push2(((uint64_t*)arrayRef->values)[indice]);
    maquina.current_frame->pc++;
}

static void op_faload(Frame *pFrame) {
    uint64_t indice, aux;
    struct _array* arrayRef;
    
    indice = maquina.current_frame->pop();
    aux = maquina.current_frame->pop();
    memcpy(&arrayRef, &aux, sizeof(uint64_t)); // convert to pointer
    
    maquina.current_frame->push(((uint32_t*)arrayRef->values)[indice]);
    maquina.current_frame->pc++;
}

static void op_daload(Frame *pFrame) {
    uint64_t indice, aux;
    struct _array *arrayRef;
    
    indice = maquina.current_frame->pop();
    aux = maquina.current_frame->pop();
    memcpy(&arrayRef, &aux, sizeof(uint64_t)); // convert to pointer
    
    maquina.current_frame->push2(((uint64_t*)arrayRef->values)[indice]);
    maquina.current_frame->pc++;
}

static void op_aaload(Frame *pFrame) {
    uint64_t indice, aux;
    struct _array *arrayRef;
    
    indice = maquina.current_frame->pop();
    aux = maquina.current_frame->pop();
    memcpy(&arrayRef, &aux, sizeof(uint64_t));
    
    maquina.current_frame->push(((uint64_t*)arrayRef->values)[indice]);
    
    maquina.current_frame->pc++;
}

static void op_baload(Frame *pFrame) {
    uint64_t indice,aux;
    struct _array* arrayRef;
    
    indice = maquina.current_frame->pop();
    aux = maquina.current_frame->pop();
    memcpy(&arrayRef, &aux, sizeof(uint64_t));
    
    maquina.current_frame->push(((int8_t*)arrayRef->values)[indice]);
    maquina.current_frame->pc++;
    
}

static void op_caload(Frame *pFrame) {
    uint64_t indice,aux;
    struct _array* arrayRef;
    
    indice = maquina.current_frame->pop();
    aux = maquina.current_frame->pop();
    memcpy(&arrayRef, &aux, sizeof(uint64_t));
    
    maquina.current_frame->push(((uint16_t*)arrayRef->values)[indice]);
    maquina.current_frame->pc++;
}

static void op_saload(Frame *pFrame) {
    uint64_t indice,aux;
    int64_t t;
    struct _array* arrayRef;
    
    indice = maquina.current_frame->pop();
    aux = maquina.current_frame->pop();
    memcpy(&arrayRef, &aux, sizeof(uint64_t));
    
    t = ((int16_t*)arrayRef->values)[indice];
    maquina.current_frame->push(t);
    maquina.current_frame->pc++;
}

static void op_istore(Frame *pFrame) {
    uint16_t indice;
    int64_t value;
    
    maquina.current_frame->pc++;
    
    indice = maquina.current_frame->code_attr->code[maquina.current_frame->pc];
    value = (int64_t)maquina.current_frame->pop();
    
    maquina.current_frame->local_variables[indice] = value;
    maquina.current_frame->pc++;
}

static void op_lstore(Frame *pFrame) {
    uint16_t indice;
    uint64_t high, low;
    
    maquina.current_frame->pc++;
    
    indice = maquina.current_frame->code_attr->code[maquina.current_frame->pc];
    low = maquina.current_frame->pop();
    high = maquina.current_frame->pop();
    
    maquina.current_frame->local_variables[indice] = high;
    maquina.current_frame->local_variables[indice+1] = low;
    
    maquina.current_frame->pc++;
}

static void op_fstore(Frame *pFrame) {
    op_istore(pFrame);
}

static void op_dstore(Frame *pFrame) {
    uint16_t indice;
    uint64_t high, low;
    
    maquina.current_frame->pc++;
    
    indice = maquina.current_frame->code_attr->code[maquina.current_frame->pc];
    low = maquina.current_frame->pop();
    high = maquina.current_frame->pop();
    
    maquina.current_frame->local_variables[indice] = high;
    maquina.current_frame->local_variables[indice+1] = low;
    
    maquina.current_frame->pc++;
}

static void op_astore(Frame *pFrame) {
    op_istore(pFrame);
}

static void op_istore_0(Frame *pFrame) {
    uint64_t value = maquina.current_frame->pop();
    
    maquina.current_frame->local_variables[0] = value;
    maquina.current_frame->pc++;
}

static void op_istore_1(Frame *pFrame) {
    int64_t value = maquina.current_frame->pop();
    
    maquina.current_frame->local_variables[1] = value;
    maquina.current_frame->pc++;
}

static void op_istore_2(Frame *pFrame) {
    uint64_t value = maquina.current_frame->pop();
    
    maquina.current_frame->local_variables[2] = value;
    maquina.current_frame->pc++;
}

static void op_istore_3(Frame *pFrame) {
    uint64_t value = maquina.current_frame->pop();
    
    maquina.current_frame->local_variables[3] = value;
    maquina.current_frame->pc++;
}

static void op_lstore_0(Frame *pFrame) {
    uint64_t high, low;
    
    low = maquina.current_frame->pop();
    high = maquina.current_frame->pop();
    
    maquina.current_frame->local_variables[0] = high;
    maquina.current_frame->local_variables[1] = low;
    maquina.current_frame->pc++;
}

static void op_lstore_1(Frame *pFrame) {
    uint64_t high, low;
    
    low = maquina.current_frame->pop();
    high = maquina.current_frame->pop();
    
    maquina.current_frame->local_variables[1]= high;
    maquina.current_frame->local_variables[2] = low;
    maquina.current_frame->pc++;
}

static void op_lstore_2(Frame *pFrame) {
    uint64_t high, low;
    
    low = maquina.current_frame->pop();
    high = maquina.current_frame->pop();
    
    maquina.current_frame->local_variables[2] = high;
    maquina.current_frame->local_variables[3] = low;
    maquina.current_frame->pc++;
}

static void op_lstore_3(Frame *pFrame) {
    uint64_t high, low;
    
    low = maquina.current_frame->pop();
    high = maquina.current_frame->pop();
    
    maquina.current_frame->local_variables[3]= high;
    maquina.current_frame->local_variables[4] = low;
    maquina.current_frame->pc++;
}

static void op_fstore_0(Frame *pFrame) {
    uint64_t  value;
    
    value = maquina.current_frame->pop();
    
    maquina.current_frame->local_variables[0] = value;
    maquina.current_frame->pc++;
}

static void op_fstore_1(Frame *pFrame) {
    op_istore_1();
}


static void op_fstore_2(Frame *pFrame) {
    op_istore_2(pFrame);
}

static void op_fstore_3(Frame *pFrame) {
    op_istore_3(pFrame);
}

static void op_dstore_0(Frame *pFrame) {
    op_lstore_0(pFrame);
}

static void op_dstore_1(Frame *pFrame) {
    op_lstore_1(pFrame);
}

static void op_dstore_2(Frame *pFrame) {
    op_lstore_2(pFrame);
}

static void op_dstore_3(Frame *pFrame) {
    op_lstore_3(pFrame);
}

static void op_astore_0(Frame *pFrame) {
    uint64_t value = maquina.current_frame->pop();
    
    maquina.current_frame->local_variables[0] = value;
    maquina.current_frame->pc++;
}

static void op_astore_1(Frame *pFrame) {
    uint64_t value = maquina.current_frame->pop();
    
    maquina.current_frame->local_variables[1] = value;
    maquina.current_frame->pc++;
}

static void op_astore_2(Frame *pFrame) {
    uint64_t value = maquina.current_frame->pop();
    
    maquina.current_frame->local_variables[2] = value;
    maquina.current_frame->pc++;
}

static void op_astore_3(Frame *pFrame) {
    uint64_t value = maquina.current_frame->pop();
    
    maquina.current_frame->local_variables[3] = value;
    maquina.current_frame->pc++;
}

static void op_iastore(Frame *pFrame) {
    uint64_t indice, value, aux;
    struct _array* arrayRef;
    
    value = maquina.current_frame->pop();
    indice = maquina.current_frame->pop();
    aux = maquina.current_frame->pop();
    
    memcpy(&arrayRef, &aux, sizeof(uint64_t));
    
    ((uint32_t*)arrayRef->values)[indice] = value;
    maquina.current_frame->pc++;
}


static void op_lastore(Frame *pFrame) {
    uint64_t indice, low, high, aux;
    long value;
    struct _array* arrayRef;
    
    
    low = maquina.current_frame->pop();
    high = maquina.current_frame->pop();
    value = getLong(high, low);
    
    indice = maquina.current_frame->pop();
    aux = maquina.current_frame->pop();
    memcpy(&arrayRef, &aux, sizeof(uint64_t));
    
    ((uint64_t*)arrayRef->values)[indice] = value;
    maquina.current_frame->pc++;
}

static void op_fastore(Frame *pFrame) {
    uint64_t indice, value, aux;
    struct _array* arrayRef;
    
    value = maquina.current_frame->pop();
    indice = maquina.current_frame->pop();
    aux = maquina.current_frame->pop();
    
    memcpy(&arrayRef, &aux, sizeof(uint64_t));
    
    ((uint32_t*)arrayRef->values)[indice] = value;
    maquina.current_frame->pc++;
}

static void op_dastore(Frame *pFrame) {
    uint64_t indice, low, high, aux,value;
    struct _array* arrayRef;
    
    
    low = maquina.current_frame->pop();
    high = maquina.current_frame->pop();
    
    value = high;
    value <<= 32;
    value += low;
    
    indice = maquina.current_frame->pop();
    aux = maquina.current_frame->pop();
    memcpy(&arrayRef, &aux, sizeof(uint64_t));
    
    ((uint64_t*)arrayRef->values)[indice] = value;
    maquina.current_frame->pc++;
}

static void op_aastore(Frame *pFrame) {
    uint64_t indice,aux,value;
    struct _array* arrayRef;
    
    value = maquina.current_frame->pop();
    indice = maquina.current_frame->pop();
    aux = maquina.current_frame->pop();
    memcpy(&arrayRef, &aux, sizeof(uint64_t));
    
    ((uint64_t*)arrayRef->values)[indice] = value;
    maquina.current_frame->pc++;
}

static void op_bastore(Frame *pFrame) {
    uint64_t indice,aux;
    uint8_t value;
    struct _array* arrayRef;
    
    value = maquina.current_frame->pop();
    indice = maquina.current_frame->pop();
    aux = maquina.current_frame->pop();
    memcpy(&arrayRef, &aux, sizeof(uint64_t));
    
    ((uint8_t*)arrayRef->values)[indice] = (uint8_t)value;
    
    maquina.current_frame->pc++;
}

static void op_castore(Frame *pFrame) {
    uint64_t indice,aux, value;
    struct _array* arrayRef;
    
    value = maquina.current_frame->pop();
    indice = maquina.current_frame->pop();
    aux = maquina.current_frame->pop();
    memcpy(&arrayRef, &aux, sizeof(uint64_t));
    
    ((uint16_t*)arrayRef->values)[indice] = value;
    
    maquina.current_frame->pc++;
}

static void op_sastore(Frame *pFrame) {
    uint64_t indice,aux;
    int64_t value;
    struct _array* arrayRef;
    
    value = maquina.current_frame->pop();
    indice = maquina.current_frame->pop();
    aux = maquina.current_frame->pop();
    memcpy(&arrayRef, &aux, sizeof(uint64_t));
    
    ((int16_t*)arrayRef->values)[indice] = (int16_t)value;
    
    maquina.current_frame->pc++;
}

static void op_pop(Frame *pFrame) {
    maquina.current_frame->pop();
    maquina.current_frame->pc++;
}

static void op_pop2(Frame *pFrame) {
    maquina.current_frame->pop();
    maquina.current_frame->pop();
    maquina.current_frame->pc++;
}

static void op_dup(Frame *pFrame) {
    uint64_t data;
    data = maquina.current_frame->pop();
    maquina.current_frame->push(data);
    maquina.current_frame->push(data);
    maquina.current_frame->pc++;
}

static void op_dup_x1(Frame *pFrame) {
    uint64_t data,other;
    data = maquina.current_frame->pop();
    other = maquina.current_frame->pop();
    maquina.current_frame->push(data);
    maquina.current_frame->push(other);
    maquina.current_frame->push(data);
    maquina.current_frame->pc++;
}

static void op_dup_x2(Frame *pFrame) {
    uint64_t data,other,last;
    data = maquina.current_frame->pop();
    other = maquina.current_frame->pop();
    last = maquina.current_frame->pop();
    maquina.current_frame->push(data);
    maquina.current_frame->push(last);
    maquina.current_frame->push(other);
    maquina.current_frame->push(data);
    maquina.current_frame->pc++;
}

static void op_dup2 (Frame *pFrame) {
    uint64_t data,other;
    data = maquina.current_frame->pop();
    other = maquina.current_frame->pop();
    maquina.current_frame->push(other);
    maquina.current_frame->push(data);
    maquina.current_frame->push(other);
    maquina.current_frame->push(data);
    maquina.current_frame->pc++;
}

static void op_dup2_x1(Frame *pFrame) {
    uint64_t data,other,last;
    data = maquina.current_frame->pop();
    other = maquina.current_frame->pop();
    last = maquina.current_frame->pop();
    maquina.current_frame->push(other);
    maquina.current_frame->push(data);
    maquina.current_frame->push(last);
    maquina.current_frame->push(other);
    maquina.current_frame->push(data);
    maquina.current_frame->pc++;
}

static void op_dup2_x2(Frame *pFrame) {
    uint64_t data,other,middle,last;
    data = maquina.current_frame->pop();
    other = maquina.current_frame->pop();
    middle = maquina.current_frame->pop();
    last = maquina.current_frame->pop();
    maquina.current_frame->push(other);
    maquina.current_frame->push(data);
    maquina.current_frame->push(last);
    maquina.current_frame->push(middle);
    maquina.current_frame->push(other);
    maquina.current_frame->push(data);
    maquina.current_frame->pc++;
}

static void op_swap(Frame *pFrame) {
    uint64_t data,other;
    data = maquina.current_frame->pop();
    other = maquina.current_frame->pop();
    maquina.current_frame->push(data);
    maquina.current_frame->push(other);
    maquina.current_frame->pc++;
}

static void op_iadd(Frame *pFrame) {
    uint64_t op,opp;
    op  = maquina.current_frame->pop();
    opp = maquina.current_frame->pop();
    
    maquina.current_frame->push(op+opp);
    maquina.current_frame->pc++;
    
}

static void op_ladd(Frame *pFrame) {
    
    uint64_t op,opp;
    uint64_t high,low;
    
    low  = maquina.current_frame->pop();
    high = maquina.current_frame->pop();
    
    op = high;
    op = op << 32;
    op = op + low;
    
    low  = maquina.current_frame->pop();
    high = maquina.current_frame->pop();
    
    opp = high;
    opp = opp << 32;
    opp = opp + low;
    
    maquina.current_frame->push2(op+opp);
    maquina.current_frame->pc++;
    
}

static void op_fadd(Frame *pFrame) {
    
    float op, opp, sum;
    uint64_t value, other,result;
    
    value = maquina.current_frame->pop();
    memcpy(&op, &value, sizeof(uint32_t));
    
    other = maquina.current_frame->pop();
    memcpy(&opp, &other, sizeof(uint32_t));
    
    sum = op + opp;
    
    memcpy(&result, &sum, sizeof(uint32_t));
    maquina.current_frame->push(result);
    
    maquina.current_frame->pc++;
}

static void op_dadd(Frame *pFrame) {
    
    uint64_t hiOp,loOp,hiOpp,loOpp;
    double sum;
    uint64_t completeValue = 0;
    
    loOp = maquina.current_frame->pop();
    hiOp = maquina.current_frame->pop();
    loOpp = maquina.current_frame->pop();
    hiOpp = maquina.current_frame->pop();
    
    sum = getDouble(hiOp,loOp) + getDouble(hiOpp,loOpp);
    memcpy(&completeValue, &sum, sizeof(uint64_t));
    
    maquina.current_frame->push2(completeValue);
    
    maquina.current_frame->pc++;
}

static void op_isub(Frame *pFrame) {
    uint64_t op,opp;
    op  = maquina.current_frame->pop();
    opp = maquina.current_frame->pop();
    maquina.current_frame->push(opp-op);
    maquina.current_frame->pc++;
}

static void op_lsub(Frame *pFrame) {
    uint64_t op,opp;
    uint64_t high,low;
    
    low  = maquina.current_frame->pop();
    high = maquina.current_frame->pop();
    
    op = high;
    op = op << 32;
    op = op + low;
    
    low  = maquina.current_frame->pop();
    high = maquina.current_frame->pop();
    
    opp = high;
    opp = opp << 32;
    opp = opp + low;
    
    maquina.current_frame->push2(opp-op);
    maquina.current_frame->pc++;
}

static void op_fsub(Frame *pFrame) {
    float op, opp, sum;
    uint64_t value, other,result;
    
    value = maquina.current_frame->pop();
    memcpy(&op, &value, sizeof(uint32_t));
    
    other = maquina.current_frame->pop();
    memcpy(&opp, &other, sizeof(uint32_t));
    
    sum = opp - op;
    
    memcpy(&result, &sum, sizeof(uint32_t));
    maquina.current_frame->push(result);
    
    maquina.current_frame->pc++;
}

static void op_dsub(Frame *pFrame) {
    double op, opp, sum;
    uint64_t result;
    uint64_t high,low;
    
    low  = maquina.current_frame->pop();
    high = maquina.current_frame->pop();
    op = getDouble(high,low);
    
    low  = maquina.current_frame->pop();
    high = maquina.current_frame->pop();
    opp = getDouble(high,low);
    
    sum = opp - op;
    
    memcpy(&result, &sum, sizeof(uint64_t));
    maquina.current_frame->push2(result);
    
    maquina.current_frame->pc++;
}

static void op_imul(Frame *pFrame) {
    uint64_t op,opp;
    op  = (int64_t)maquina.current_frame->pop();
    opp = (int64_t)maquina.current_frame->pop();
    maquina.current_frame->push(op*opp);
    maquina.current_frame->pc++;
}

static void op_lmul(Frame *pFrame) {
    
    int64_t hop, lop, hopp, lopp;
    int64_t op, opp;
    
    lop  = maquina.current_frame->pop();
    hop  = maquina.current_frame->pop();
    lopp = maquina.current_frame->pop();
    hopp = maquina.current_frame->pop();
    
    op  = hop;
    op  = op << 32;
    op  = op + lop;
    
    opp  = hopp;
    opp  = opp << 32;
    opp  = opp + lopp;
    
    maquina.current_frame->push2((int64_t)(op*opp));
    maquina.current_frame->pc++;
    
}

static void op_fmul(Frame *pFrame) {
    float op, opp, mult;
    uint64_t value, other,result;
    
    value = maquina.current_frame->pop();
    memcpy(&op, &value, sizeof(uint32_t));
    
    other = maquina.current_frame->pop();
    memcpy(&opp, &other, sizeof(uint32_t));
    
    mult = op * opp;
    
    memcpy(&result, &mult, sizeof(uint32_t));
    maquina.current_frame->push(result);
    
    maquina.current_frame->pc++;
}

static void op_dmul(Frame *pFrame) {
    int64_t hop, lop, hopp, lopp;
    double op, opp, mult;
    uint64_t final;
    
    lop  = maquina.current_frame->pop();
    hop  = maquina.current_frame->pop();
    lopp = maquina.current_frame->pop();
    hopp = maquina.current_frame->pop();
    
    op  = getDouble(hop,lop);
    opp  = getDouble(hopp,lopp);
    mult = op*opp;
    
    memcpy(&final, &mult, sizeof(int64_t));
    maquina.current_frame->push2((final));
    
    maquina.current_frame->pc++;
}

static void op_idiv(Frame *pFrame) {
    uint64_t op,opp;
    op  = (int64_t)maquina.current_frame->pop();
    opp = (int64_t)maquina.current_frame->pop();
    maquina.current_frame->push(opp/op);
    maquina.current_frame->pc++;
}

static void op_ldiv(Frame *pFrame) {
    
    int64_t hop, lop, hopp, lopp;
    int64_t op, opp;
    
    lop  = maquina.current_frame->pop();
    hop  = maquina.current_frame->pop();
    lopp = maquina.current_frame->pop();
    hopp = maquina.current_frame->pop();
    
    op  = hop;
    op  = op << 32;
    op  = op + lop;
    
    opp  = hopp;
    opp  = opp << 32;
    opp  = opp + lopp;
    
    maquina.current_frame->push2((int64_t)(opp/op));
    
    maquina.current_frame->pc++;
}

static void op_fdiv(Frame *pFrame) {
    float op, opp, mult;
    uint64_t value, other,result;
    
    value = maquina.current_frame->pop();
    memcpy(&op, &value, sizeof(uint32_t));
    
    other = maquina.current_frame->pop();
    memcpy(&opp, &other, sizeof(uint32_t));
    
    mult = opp/op;
    
    memcpy(&result, &mult, sizeof(uint32_t));
    maquina.current_frame->push((uint64_t)(result));
    
    maquina.current_frame->pc++;
}

static void op_ddiv(Frame *pFrame) {
    int64_t hop, lop, hopp, lopp, final;
    double op, opp, div;
    
    lop  = maquina.current_frame->pop();
    hop  = maquina.current_frame->pop();
    lopp = maquina.current_frame->pop();
    hopp = maquina.current_frame->pop();
    
    op  = getDouble(hop,lop);
    opp  = getDouble(hopp,lopp);
    div = opp/op;
    
    memcpy(&final, &div, sizeof(int64_t));
    maquina.current_frame->push2(final);
    
    maquina.current_frame->pc++;
}

static void op_irem(Frame *pFrame) {
    uint64_t op,opp;
    op  = maquina.current_frame->pop();
    opp = maquina.current_frame->pop();
    maquina.current_frame->push(opp%op);
    maquina.current_frame->pc++;
}

static void op_lrem(Frame *pFrame) {
    uint64_t op,opp;
    uint64_t high,low;
    
    low  = maquina.current_frame->pop();
    high = maquina.current_frame->pop();
    
    op = high;
    op = op << 32;
    op = op + low;
    
    low  = maquina.current_frame->pop();
    high = maquina.current_frame->pop();
    
    opp = high;
    opp = opp << 32;
    opp = opp + low;
    
    maquina.current_frame->push2(opp%op);
    maquina.current_frame->pc++;
}

static void op_frem(Frame *pFrame) {
    float op, opp, mod;
    uint64_t value2, value1, result;
    
    value2 = maquina.current_frame->pop();
    memcpy(&op, &value2, sizeof(uint32_t));
    
    value1 = maquina.current_frame->pop();
    memcpy(&opp, &value1, sizeof(uint32_t));
    
    mod = fmodf(opp , op);
    memcpy(&result, &mod, sizeof(uint32_t));
    
    maquina.current_frame->push(result);
    maquina.current_frame->pc++;
    
}

static void op_drem(Frame *pFrame) {
    uint64_t hop, lop, hopp, lopp;
    double op, opp, mod;
    uint64_t final;
    
    lop  = maquina.current_frame->pop();
    hop  = maquina.current_frame->pop();
    lopp = maquina.current_frame->pop();
    hopp = maquina.current_frame->pop();
    
    op  = getDouble(hop,lop);
    opp  = getDouble(hopp,lopp);
    mod = fmod(opp,op);
    
    memcpy(&final, &mod, sizeof(uint64_t));
    
    maquina.current_frame->push2(final);
    maquina.current_frame->pc++;
}

static void op_ineg(Frame *pFrame) {
    int64_t op;
    uint64_t aux = 0;
    
    op  = -maquina.current_frame->pop();
    memcpy(&aux, &op, sizeof(uint64_t));
    maquina.current_frame->push(aux);
    
    maquina.current_frame->pc++;
}

static void op_lneg(Frame *pFrame) {
    uint64_t op;
    uint64_t high,low;
    
    low  = maquina.current_frame->pop();
    high = maquina.current_frame->pop();
    
    op = high;
    op = op << 32;
    op = op + low;
    
    op = -(op);
    
    maquina.current_frame->push2(op);
    maquina.current_frame->pc++;
}

static void op_fneg(Frame *pFrame) {
    float op, negative;
    uint64_t value, result;
    
    value = maquina.current_frame->pop();
    memcpy(&op, &value, sizeof(uint32_t));
    
    negative = -op;
    
    memcpy(&result, &negative, sizeof(uint32_t));
    maquina.current_frame->push(result);
    
    maquina.current_frame->pc++;
}

static void op_dneg(Frame *pFrame) {
    double op, negative;
    uint64_t result;
    uint64_t high,low;
    
    low  = maquina.current_frame->pop();
    high = maquina.current_frame->pop();
    op = getDouble(high,low);
    
    negative = -op;
    
    memcpy(&result, &negative, sizeof(uint64_t));
    maquina.current_frame->push2(result);
    
    maquina.current_frame->pc++;
}

static void op_ishl(Frame *pFrame) {
    uint64_t lowsFive = 0x1f;
    uint64_t value1, value2;
    
    value2 = maquina.current_frame->pop();
    value2 = value2 & lowsFive;
    
    value1 = maquina.current_frame->pop();
    value1 = value1 << value2;
    
    maquina.current_frame->push(value1);
    
    maquina.current_frame->pc++;
}

static void op_lshl(Frame *pFrame) {
    int64_t bigBits;
    uint64_t lowSix = 0x3f;
    uint64_t low, high, result;
    
    result = maquina.current_frame->pop();
    result = result & lowSix;
    
    
    low = maquina.current_frame->pop();
    high = maquina.current_frame->pop();
    
    
    
    bigBits = high;
    bigBits = bigBits << 32;
    bigBits = (signed)(bigBits + low);
    bigBits = bigBits << result;
    
    maquina.current_frame->push2(bigBits);
    
    maquina.current_frame->pc++;
}

static void op_ishr(Frame *pFrame) {
    
    int32_t value1,lowFive = 0x1f;
    int32_t value2;
    
    value1 = maquina.current_frame->pop();
    value1 = value1 & lowFive;
    value2 = (signed)(int32_t)maquina.current_frame->pop();
    
    for(int j = 0; j < value1; j++) {
        value2 = value2 / 2;
    }
    
    maquina.current_frame->push((int64_t)value2);
    maquina.current_frame->pc++;
}

static void op_lshr(Frame *pFrame) {
    
    uint64_t allOne = 0xffffffffffffffff, firstOne = 0x8000000000000000, var;
    uint64_t low, high, vartwo, lowSeven = 0x3f;;
    
    vartwo = maquina.current_frame->pop();
    vartwo = vartwo & lowSeven;
    
    allOne = allOne << (64-vartwo);
    low = maquina.current_frame->pop();
    high = maquina.current_frame->pop();
    
    
    var = high;
    var = var << 32;
    var = (signed)(var + low);
    
    firstOne = var & firstOne;
    var = var >> vartwo;
    
    if(firstOne == 1) {
        var = var | allOne;
    }
    
    maquina.current_frame->push2((uint64_t)var);
    
    maquina.current_frame->pc++;
}

static void op_iushr(Frame *pFrame) {
    uint64_t lowFive = 0x1f;
    uint64_t value, other;
    
    other = maquina.current_frame->pop();
    other = other & lowFive;
    value = maquina.current_frame->pop();
    value = value >> other;
    maquina.current_frame->push(value);
    maquina.current_frame->pc++;
}

static void op_lushr(Frame *pFrame) {
    int64_t bigBits;
    uint64_t var, low, high, lowFive = 0x3f;
    
    var = maquina.current_frame->pop();
    var = var & lowFive;
    
    low = maquina.current_frame->pop();
    high = maquina.current_frame->pop();
    
    bigBits = high;
    bigBits = bigBits << 32;
    bigBits = (signed)(bigBits + low);
    
    bigBits = bigBits >> var;
    maquina.current_frame->push2((uint64_t)bigBits);
    
    maquina.current_frame->pc++;
}

static void op_iand(Frame *pFrame) {
    uint64_t op,opp;
    op  = maquina.current_frame->pop();
    opp = maquina.current_frame->pop();
    maquina.current_frame->push(op&opp);
    maquina.current_frame->pc++;
}

static void op_land(Frame *pFrame) {
    
    uint64_t op,opp;
    uint64_t high,low;
    
    low  = maquina.current_frame->pop();
    high = maquina.current_frame->pop();
    
    op = high;
    op = op << 32;
    op = op + low;
    
    low  = maquina.current_frame->pop();
    high = maquina.current_frame->pop();
    
    opp = high;
    opp = opp << 32;
    opp = opp + low;
    
    maquina.current_frame->push2(op&opp);
    maquina.current_frame->pc++;
}

static void op_ior(Frame *pFrame) {
    uint64_t op,opp;
    op  = maquina.current_frame->pop();
    opp = maquina.current_frame->pop();
    maquina.current_frame->push(op|opp);
    maquina.current_frame->pc++;
}

static void op_lor(Frame *pFrame) {
    uint64_t op,opp;
    uint64_t high,low;
    
    low  = maquina.current_frame->pop();
    high = maquina.current_frame->pop();
    
    op = high;
    op = op << 32;
    op = op + low;
    
    low  = maquina.current_frame->pop();
    high = maquina.current_frame->pop();
    
    opp = high;
    opp = opp << 32;
    opp = opp + low;
    
    maquina.current_frame->push2(op|opp);
    maquina.current_frame->pc++;
}

static void op_ixor(Frame *pFrame) {
    uint64_t op,opp;
    op  = maquina.current_frame->pop();
    opp = maquina.current_frame->pop();
    maquina.current_frame->push(op^opp);
    maquina.current_frame->pc++;
}

static void op_lxor(Frame *pFrame) {
    uint64_t op,opp;
    uint64_t high,low;
    
    low  = maquina.current_frame->pop();
    high = maquina.current_frame->pop();
    
    op = high;
    op = op << 32;
    op = op + low;
    
    low  = maquina.current_frame->pop();
    high = maquina.current_frame->pop();
    
    opp = high;
    opp = opp << 32;
    opp = opp + low;
    
    maquina.current_frame->push2(op^opp);
    maquina.current_frame->pc++;
}

static void op_iinc(Frame *pFrame) {
    uint8_t field_index = maquina.current_frame->code_attr->code[++(maquina.current_frame->pc)];
    uint64_t auxiliar = maquina.current_frame->local_variables[field_index];
    uint8_t auxiliar2 = maquina.current_frame->code_attr->code[++(maquina.current_frame->pc)];
    int8_t index = (int8_t) auxiliar;
    int8_t constant = (int8_t) auxiliar2;
    
    
    index += constant;
    maquina.current_frame->local_variables[field_index] = (uint64_t) index;
    maquina.current_frame->pc++;
}

static void op_i2l(Frame *pFrame) {
    uint64_t value1, value3, oneOne = 0x80000000;
    uint64_t bigBits,getHigh = 0xffffffff00000000;
    
    value1 = maquina.current_frame->pop();
    value3 = value1 & oneOne;
    bigBits = (int64_t) value1;
    
    if(value3 == 1) {
        bigBits = bigBits | getHigh;
    }
    
    maquina.current_frame->push2(bigBits);
    maquina.current_frame->pc++;
}

static void op_i2f(Frame *pFrame) {
    
    uint64_t value;
    uint64_t value2 = 0;
    
    float number;
    
    value = maquina.current_frame->pop();
    
    number = (float)value;
    
    memcpy(&value2, &number, sizeof(float));
    maquina.current_frame->push(value2);
    
    maquina.current_frame->pc++;
}

static void op_i2d(Frame *pFrame) {
    
    uint64_t value;
    uint64_t value2 = 0;
    
    double number;
    
    value = maquina.current_frame->pop();
    
    number = (double)value;
    
    memcpy(&value2, &number, sizeof(double));
    maquina.current_frame->push2(value2);
    
    maquina.current_frame->pc++;
}

static void op_l2i(Frame *pFrame) {
    uint64_t low;
    low = maquina.current_frame->pop();
    maquina.current_frame->pop();
    maquina.current_frame->push(low);
    
    maquina.current_frame->pc++;
}

static void op_l2f(Frame *pFrame) {
    uint64_t low, high, toPush;
    long val;
    float number;
    
    low = maquina.current_frame->pop();
    high = maquina.current_frame->pop();
    
    val = getLong(high, low);
    number = (float)val;
    memcpy(&toPush, &number, sizeof(uint32_t));
    
    maquina.current_frame->push(toPush);
    maquina.current_frame->pc++;
}


static void op_l2d(Frame *pFrame) {
    uint64_t low, high, toPush = 0;
    long val;
    double number;
    
    low = maquina.current_frame->pop();
    high = maquina.current_frame->pop();
    
    val = getLong(high, low);
    
    number = (double)val;
    memcpy(&toPush, &number, sizeof(uint64_t));
    
    maquina.current_frame->push2(toPush);
    maquina.current_frame->pc++;
}

static void op_f2i(Frame *pFrame) {
    uint64_t value;
    float number;
    
    value = maquina.current_frame->pop();
    memcpy(&number, &value, sizeof(uint32_t));
    value = (uint64_t) number;
    
    maquina.current_frame->push(value);
    
    maquina.current_frame->pc++;
}

static void op_f2l(Frame *pFrame) {
    
    uint64_t value;
    uint64_t other;
    float number;
    
    value = maquina.current_frame->pop();
    memcpy(&number, &value, sizeof(uint32_t));
    
    other = (uint64_t) number;
    maquina.current_frame->push2(other);
    
    maquina.current_frame->pc++;
}

static void op_f2d(Frame *pFrame) {
    
    uint64_t value;
    uint64_t other;
    
    double double_number;
    float float_number;
    
    value = maquina.current_frame->pop();
    memcpy(&float_number, &value, sizeof(uint32_t));
    
    double_number = (double) float_number;
    memcpy(&other, &double_number, sizeof(uint64_t));
    
    maquina.current_frame->push2(other);
    
    maquina.current_frame->pc++;
}

static void op_d2i(Frame *pFrame) {
    
    int64_t hop, lop;
    double op;
    uint64_t final;
    int64_t int_number;
    
    lop  = maquina.current_frame->pop();
    hop  = maquina.current_frame->pop();
    
    op  = getDouble(hop,lop);
    
    int_number = (int64_t)op;
    
    memcpy(&final, &int_number, sizeof(int64_t));
    
    maquina.current_frame->push((final));
    
    maquina.current_frame->pc++;
}

static void op_d2l(Frame *pFrame) {
    
    int64_t hop, lop;
    double op;
    uint64_t final;
    long long_number;
    
    lop  = maquina.current_frame->pop();
    hop  = maquina.current_frame->pop();
    
    op  = getDouble(hop,lop);
    
    long_number = (long)op;
    
    memcpy(&final, &long_number, sizeof(int64_t));
    
    maquina.current_frame->push2((final));
    
    maquina.current_frame->pc++;
    
}

static void op_d2f(Frame *pFrame) {
    
    int64_t hop, lop;
    double op;
    uint32_t final;
    float float_number;
    
    lop  = maquina.current_frame->pop();
    hop  = maquina.current_frame->pop();
    
    op  = getDouble(hop,lop);
    
    float_number = (float) op;
    
    memcpy(&final, &float_number, sizeof(int32_t));
    maquina.current_frame->push((final));
    
    maquina.current_frame->pc++;
}

static void op_i2b(Frame *pFrame) {
    
    int8_t value;
    int64_t other;
    
    value = (int8_t) maquina.current_frame->pop();
    other = (int64_t)value;
    maquina.current_frame->push((int64_t)other);
    
    maquina.current_frame->pc++;
}

static void op_i2c(Frame *pFrame) {
    
    int16_t value;
    int64_t other;
    
    value = (int16_t) maquina.current_frame->pop();
    other = (int64_t)value;
    maquina.current_frame->push((int64_t)other);
    
    maquina.current_frame->pc++;
}

static void op_i2s(Frame *pFrame) {
    
    int16_t value;
    int64_t other;
    
    value = (int16_t) maquina.current_frame->pop();
    other = (int64_t)value;
    
    maquina.current_frame->push((uint64_t)other);
    
    maquina.current_frame->pc++;
}

static void op_lcmp(Frame *pFrame) {
    
    int64_t result;
    int64_t low, high;
    int64_t value, other;
    
    low = maquina.current_frame->pop();
    high = maquina.current_frame->pop();
    other = getLong(high, low);
    
    low = maquina.current_frame->pop();
    high = maquina.current_frame->pop();
    
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
    
    maquina.current_frame->push(result);
    maquina.current_frame->pc++;
}

static void op_fcmpl(Frame *pFrame) {
    
    int64_t empilha;
    uint64_t value;
    float op, opp;
    
    value = maquina.current_frame->pop();
    
    memcpy(&opp, &value, sizeof(uint32_t));
    value = maquina.current_frame->pop();
    
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
    
    maquina.current_frame->push((uint64_t) empilha);
    maquina.current_frame->pc++;
}

static void op_fcmpg(Frame *pFrame) {
    
    float value, other;
    uint64_t auxiliar;
    
    int64_t resultado;
    
    auxiliar = maquina.current_frame->pop();
    memcpy(&other, &auxiliar, sizeof(uint32_t));
    
    auxiliar = maquina.current_frame->pop();
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
    
    maquina.current_frame->push((uint64_t) resultado);
    maquina.current_frame->pc++;
}

static void op_dcmpl(Frame *pFrame) {
    double double_number, double_number2;
    uint64_t low, high;
    int64_t empilha;
    
    low = maquina.current_frame->pop();
    high = maquina.current_frame->pop();
    
    double_number2 = getDouble(high, low);
    
    low = maquina.current_frame->pop();
    high = maquina.current_frame->pop();
    
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
    
    maquina.current_frame->push((uint64_t) empilha);
    maquina.current_frame->pc++;
}

static void op_dcmpg(Frame *pFrame) {
    double double_number, double_number2;
    uint64_t low, high;
    int64_t empilha;
    
    low = maquina.current_frame->pop();
    high = maquina.current_frame->pop();
    
    double_number2 = getDouble(high, low);
    
    low = maquina.current_frame->pop();
    high = maquina.current_frame->pop();
    
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
    
    maquina.current_frame->push((uint64_t) empilha);
    maquina.current_frame->pc++;
    
}

static void op_ifeq(Frame *pFrame) {
    
    uint8_t pathOne, pathTwo;
    int16_t desloc;
    int64_t value;
    
    pathOne = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+1];
    pathTwo = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+2];
    
    value = (signed) maquina.current_frame->pop();
    if(value == 0) {
        
        desloc = pathOne;
        desloc = desloc << 8;
        desloc = desloc | pathTwo;
        
        maquina.current_frame->pc = maquina.current_frame->pc + desloc;
        
    } else {
        maquina.current_frame->pc = maquina.current_frame->pc + 3;
    }
}


static void op_ifne(Frame *pFrame) {
    
    uint8_t pathOne, pathTwo;
    int16_t desloc;
    int64_t value;
    
    pathOne = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+1];
    pathTwo = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+2];
    
    value = (signed) maquina.current_frame->pop();
    if(value != 0) {
        
        desloc = pathOne;
        desloc = desloc << 8;
        desloc = desloc | pathTwo;
        
        maquina.current_frame->pc = maquina.current_frame->pc + desloc;
        
    } else {
        maquina.current_frame->pc = maquina.current_frame->pc + 3;
    }
}

static void op_iflt(Frame *pFrame) {
    
    uint8_t pathOne, pathTwo;
    int16_t desloc;
    int64_t value;
    
    pathOne = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+1];
    pathTwo = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+2];
    
    value = (signed) maquina.current_frame->pop();
    if(value < 0) {
        
        desloc = pathOne;
        desloc = desloc << 8;
        desloc = desloc | pathTwo;
        
        maquina.current_frame->pc = maquina.current_frame->pc + desloc;
        
    } else {
        maquina.current_frame->pc = maquina.current_frame->pc + 3;
    }
}

static void op_ifge(Frame *pFrame) {
    
    uint8_t pathOne, pathTwo;
    int16_t desloc;
    int64_t value;
    
    pathOne = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+1];
    pathTwo = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+2];
    
    value = (signed) maquina.current_frame->pop();
    if(value >= 0) {
        
        desloc = pathOne;
        desloc = desloc << 8;
        desloc = desloc | pathTwo;
        
        maquina.current_frame->pc = maquina.current_frame->pc + desloc;
        
    } else {
        maquina.current_frame->pc = maquina.current_frame->pc + 3;
    }
    
}

static void op_ifgt(Frame *pFrame) {
    
    uint8_t pathOne, pathTwo;
    int16_t desloc;
    int64_t value;
    
    pathOne = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+1];
    pathTwo = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+2];
    
    value = (signed) maquina.current_frame->pop();
    if(value > 0) {
        
        desloc = pathOne;
        desloc = desloc << 8;
        desloc = desloc | pathTwo;
        
        maquina.current_frame->pc = maquina.current_frame->pc + desloc;
        
    } else {
        maquina.current_frame->pc = maquina.current_frame->pc + 3;
    }
    
}

static void op_ifle(Frame *pFrame) {
    
    uint8_t pathOne, pathTwo;
    uint16_t desloc;
    int64_t value;
    
    pathOne = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+1];
    pathTwo = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+2];
    
    value = (signed) maquina.current_frame->pop();
    
    if(value <= 0) {
        desloc = pathOne;
        desloc = desloc << 8;
        desloc = desloc | pathTwo;
        
        maquina.current_frame->pc = maquina.current_frame->pc + desloc;
        
    } else {
        maquina.current_frame->pc = maquina.current_frame->pc + 3;
    }
}

static void op_if_icmpeq(Frame *pFrame) {
    
    int8_t pathOne, pathTwo;
    int64_t value1, value2;
    int16_t desloc;
    
    pathOne = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+1];
    pathTwo = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+2];
    
    value2 = (signed) maquina.current_frame->pop();
    value1 = (signed) maquina.current_frame->pop();
    
    if(value1 == value2) {
        
        desloc = pathOne;
        desloc = desloc << 8;
        desloc = desloc | pathTwo;
        
        maquina.current_frame->pc = maquina.current_frame->pc + desloc;
        
    } else {
        maquina.current_frame->pc = maquina.current_frame->pc + 3;
    }
    
}

static void op_if_icmpne(Frame *pFrame) {
    
    int8_t pathOne, pathTwo;
    int64_t value1, value2;
    int16_t desloc;
    
    pathOne = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+1];
    pathTwo = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+2];
    
    value2 = (signed) maquina.current_frame->pop();
    value1 = (signed) maquina.current_frame->pop();
    
    if(value1 != value2) {
        
        desloc = pathOne;
        desloc = desloc << 8;
        desloc = desloc | pathTwo;
        
        maquina.current_frame->pc = maquina.current_frame->pc + desloc;
        
    } else {
        maquina.current_frame->pc = maquina.current_frame->pc + 3;
    }
    
}

static void op_if_icmplt(Frame *pFrame) {
    
    int8_t pathOne, pathTwo;
    int64_t value1, value2;
    int16_t desloc;
    
    pathOne = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+1];
    pathTwo = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+2];
    
    value2 = (signed) maquina.current_frame->pop();
    value1 = (signed) maquina.current_frame->pop();
    
    if(value1 < value2) {
        
        desloc = pathOne;
        desloc = desloc << 8;
        desloc = desloc | pathTwo;
        
        maquina.current_frame->pc = maquina.current_frame->pc + desloc;
        
    } else {
        maquina.current_frame->pc = maquina.current_frame->pc + 3;
    }
    
}

static void op_if_icmpge(Frame *pFrame) {
    
    int8_t pathOne, pathTwo;
    int64_t value1, value2;
    int16_t desloc;
    
    pathOne = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+1];
    pathTwo = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+2];
    
    value2 = (signed) maquina.current_frame->pop();
    value1 = (signed) maquina.current_frame->pop();
    
    if(value1 >= value2) {
        
        desloc = pathOne;
        desloc = desloc << 8;
        desloc = desloc | pathTwo;
        
        maquina.current_frame->pc = maquina.current_frame->pc + desloc;
        
    } else {
        maquina.current_frame->pc = maquina.current_frame->pc + 3;
    }
    
}

static void op_if_icmpgt(Frame *pFrame) {
    
    int8_t pathOne, pathTwo;
    int64_t value1, value2;
    int16_t desloc;
    
    pathOne = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+1];
    pathTwo = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+2];
    
    value2 = (signed) maquina.current_frame->pop();
    value1 = (signed) maquina.current_frame->pop();
    
    if(value1 > value2) {
        
        desloc = pathOne;
        desloc = desloc << 8;
        desloc = desloc | pathTwo;
        
        maquina.current_frame->pc = maquina.current_frame->pc + desloc;
        
    } else {
        maquina.current_frame->pc = maquina.current_frame->pc + 3;
    }
    
}

static void op_if_icmple(Frame *pFrame) {
    
    int8_t pathOne, pathTwo;
    int64_t value1, value2;
    int16_t desloc;
    
    pathOne = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+1];
    pathTwo = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+2];
    
    value2 = (signed) maquina.current_frame->pop();
    value1 = (signed) maquina.current_frame->pop();
    
    if(value1 <= value2) {
        
        desloc = pathOne;
        desloc = desloc << 8;
        desloc = desloc | pathTwo;
        
        maquina.current_frame->pc = maquina.current_frame->pc + desloc;
        
    } else {
        maquina.current_frame->pc = maquina.current_frame->pc + 3;
    }
    
}

static void op_if_acmpeg(Frame *pFrame) {
    
    int8_t pathOne, pathTwo;
    int64_t value1, value2;
    int16_t desloc;
    
    pathOne = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+1];
    pathTwo = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+2];
    
    value2 = (signed) maquina.current_frame->pop();
    value1 = (signed) maquina.current_frame->pop();
    
    if(value1 == value2) {
        
        desloc = pathOne;
        desloc = desloc << 8;
        desloc = desloc | pathTwo;
        
        maquina.current_frame->pc = maquina.current_frame->pc + desloc;
        
    } else {
        maquina.current_frame->pc = maquina.current_frame->pc + 3;
    }
    
}

static void op_if_acmpne(Frame *pFrame) {
    
    int8_t pathOne, pathTwo;
    int64_t value1, value2;
    int16_t desloc;
    
    pathOne = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+1];
    pathTwo = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+2];
    
    value2 = (signed) maquina.current_frame->pop();
    value1 = (signed) maquina.current_frame->pop();
    
    if(value1 != value2) {
        
        desloc = pathOne;
        desloc = desloc << 8;
        desloc = desloc | pathTwo;
        
        maquina.current_frame->pc = maquina.current_frame->pc + desloc;
        
    } else {
        maquina.current_frame->pc = maquina.current_frame->pc + 3;
    }
    
}

static void op_goto(Frame *pFrame) {
    uint8_t pathOne, pathTwo;
    int16_t desloc;
    pathOne = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+1];
    pathTwo = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+2];
    
    desloc = pathOne;
    desloc = desloc << 8;
    desloc = desloc | pathTwo;
    
    maquina.current_frame->pc += desloc;
}

static void op_jsr(Frame *pFrame) {
    
    uint8_t pathOne, pathTwo;
    int16_t desloc;
    
    maquina.current_frame->push((maquina.current_frame->pc) + 3);
    pathOne = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+1];
    pathTwo = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+2];
    
    desloc = pathOne;
    desloc = desloc << 8;
    desloc = desloc | pathTwo;
    
    maquina.current_frame->pc = maquina.current_frame->pc + desloc;
    
}

static void op_ret(Frame *pFrame) {
    
    int16_t indice;
    maquina.current_frame->pc++;
    indice = maquina.current_frame->code_attr->code[maquina.current_frame->pc];
    
    if(WIDE == 1){
        indice = indice << 8;
        maquina.current_frame->pc++;
        indice = indice | maquina.current_frame->code_attr->code[maquina.current_frame->pc];
        WIDE = 0;
    }
    maquina.current_frame->pc = maquina.current_frame->local_variables[indice];
}

static void op_tableswitch(Frame *pFrame) {
    
    int padrao, hi, lo, index, i ,j;
    int *tabelao;
    
    uint64_t locate,saltar, tableSize, desloc, bytes[5];
    
    index = maquina.current_frame->pop();
    locate = maquina.current_frame->pc;
    
    while((maquina.current_frame->pc + 1) % 4 != 0)
        maquina.current_frame->pc++;
    
    maquina.current_frame->pc++;
    
    for(i = 0; i < 4; i++)
        bytes[i] = (uint64_t)maquina.current_frame->code_attr->code[maquina.current_frame->pc++];
    
    padrao = ( (bytes[0] & 0xFF) << 24) |((bytes[1] & 0xFF) << 16) |((bytes[2] & 0xFF) << 8) |(bytes[3] & 0xFF);
    
    
    for(i = 0; i < 4; i++)
        bytes[i] = (uint64_t)maquina.current_frame->code_attr->code[maquina.current_frame->pc++];
    
    lo = ((bytes[0] & 0xFF) << 24) |((bytes[1] & 0xFF) << 16) |((bytes[2] & 0xFF) << 8) |(bytes[3] & 0xFF);
    
    for(i = 0; i < 4; i++)
        bytes[i] = (uint64_t)maquina.current_frame->code_attr->code[maquina.current_frame->pc++];
    
    hi = ((bytes[0] & 0xFF) << 24) |((bytes[1] & 0xFF) << 16) |((bytes[2] & 0xFF) << 8) |(bytes[3] & 0xFF);
    
    tableSize = (hi-lo) + 1;
    tabelao = calloc(sizeof(uint64_t), tableSize);
    
    
    for(i = 0; i < tableSize; i++) 	{
        
        for(j = 0; j < 4; j++) 	{
            bytes[j] = (uint64_t)maquina.current_frame->code_attr->code[maquina.current_frame->pc++];
        }
        
        tabelao[i] = ((bytes[0] & 0xFF) << 24) |((bytes[1] & 0xFF) << 16) |((bytes[2] & 0xFF) << 8) |(bytes[3] & 0xFF);
    }
    
    if(index > hi || index < lo ) {
        
        saltar = locate + padrao;
        
    } else {
        
        desloc = tabelao[index - lo];
        
        saltar = locate + desloc;
    }
    
    maquina.current_frame->pc = saltar;
    
}


static void op_lookupswitch(Frame *pFrame) {
    
    int padrao, index, i ,j, pairs,found;
    uint64_t locate,saltar, bytes[5];
    int32_t *match, *offset;
    
    index = maquina.current_frame->pop();
    locate = maquina.current_frame->pc;
    
    while((maquina.current_frame->pc + 1) % 4 != 0)
        maquina.current_frame->pc++;
    
    maquina.current_frame->pc++;
    
    for(i = 0; i < 4; i++)
        bytes[i] = (uint64_t)maquina.current_frame->code_attr->code[maquina.current_frame->pc++];
    
    padrao = ( (bytes[0] & 0xFF) << 24) |((bytes[1] & 0xFF) << 16) |((bytes[2] & 0xFF) << 8) |(bytes[3] & 0xFF);
    
    
    for(i = 0; i < 4; i++)
        bytes[i] = (uint64_t)maquina.current_frame->code_attr->code[maquina.current_frame->pc++];
    
    pairs = ((bytes[0] & 0xFF) << 24) |((bytes[1] & 0xFF) << 16) |((bytes[2] & 0xFF) << 8) |(bytes[3] & 0xFF);
    
    
    match = calloc(sizeof(int32_t), pairs);
    offset = calloc(sizeof(int32_t), pairs);
    
    for(i = 0; i < pairs; i++) {
        
        for(j = 0; j < 4; j++) 	{
            bytes[j] = (uint64_t)maquina.current_frame->code_attr->code[maquina.current_frame->pc++];
        }
        
        match[i] = ((bytes[0] & 0xFF) << 24) |((bytes[1] & 0xFF) << 16) |((bytes[2] & 0xFF) << 8) | (bytes[3] & 0xFF);
        
        for(j = 0; j < 4; j++) 	{
            bytes[j] = (uint64_t)maquina.current_frame->code_attr->code[maquina.current_frame->pc++];
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
    
    maquina.current_frame->pc = saltar;
    
}


static void op_ireturn(Frame *pFrame) {
    uint64_t aux = maquina.current_frame->pop();
    
    maquina.stack->popFrame();
    maquina.stack->have_returned = 1;
    
    if (maquina.current_frame) {
        maquina.current_frame->push(aux);
    }
    
}

static void op_lreturn(Frame *pFrame) {
    uint64_t low = maquina.current_frame->pop();
    uint64_t high = maquina.current_frame->pop();
    maquina.stack->popFrame();
    maquina.stack->have_returned = 1;
    
    if (maquina.current_frame) {
        maquina.current_frame->push2(getLong(high,low));
    }
}

static void op_freturn(Frame *pFrame) {
    op_ireturn(pFrame);
}

static void op_dreturn(Frame *pFrame) {
    uint64_t low = maquina.current_frame->pop();
    uint64_t high = maquina.current_frame->pop();
    
    maquina.stack->popFrame();
    maquina.stack->have_returned = 1;
    
    if (maquina.current_frame) {
        
        maquina.current_frame->push(high);
        maquina.current_frame->push(low);
    }
    
}

static void op_areturn(Frame *pFrame) {
    op_ireturn(pFrame);
}

static void op_return(Frame *pFrame) {
    maquina.stack->popFrame();
    maquina.stack->have_returned = 1;
}

static void op_getstatic(Frame *pFrame) {
    // printf("\n\t\t\t\tentrou getstatic: %p; method_area: %p", maquina.current_frame, maquina.method_area);
    uint8_t index_1, index_2;
    uint16_t indice, nameTypeIndex;
    uint64_t classIndexTemp;
    int32_t classIndex, field_index;
    uint64_t valor;
    char *className, *name, *type;
    
    index_1 = (uint8_t) maquina.current_frame->code_attr->code[++(maquina.current_frame->pc)];
    index_2 = (uint8_t) maquina.current_frame->code_attr->code[++(maquina.current_frame->pc)];
    indice = ((uint16_t)index_1 << 8) |(uint16_t)index_2;
    
    classIndexTemp = maquina.current_frame->runtime_constant_pool->constants[indice-1].type.FieldRef.classIndex;
    className = maquina.current_frame->runtime_constant_pool->getUtf8String(maquina.current_frame->runtime_constant_pool, maquina.current_frame->runtime_constant_pool->constants[classIndexTemp-1].type.Class.nameIndex);
    
    nameTypeIndex = maquina.current_frame->runtime_constant_pool->constants[indice-1].type.FieldRef.nameTypeIndex;
    name = maquina.current_frame->runtime_constant_pool->getUtf8String(maquina.current_frame->runtime_constant_pool, maquina.current_frame->runtime_constant_pool->constants[nameTypeIndex-1].type.NameType.nameIndex);
    type = maquina.current_frame->runtime_constant_pool->getUtf8String(maquina.current_frame->runtime_constant_pool, maquina.current_frame->runtime_constant_pool->constants[nameTypeIndex-1].type.NameType.descriptorIndex);
    
    
    while((field_index = maquina.retrieveFieldIndex(className, name, strlen(name), type, strlen(type))) == -1) {
        className = _MCLASS.getParentName(maquina.getClassByName(className));
    }
    
    classIndex = maquina.loadClass(className);
    
    if(field_index < 0){
        field_index = maquina.searchStaticFieldVal(classIndex,name,type);
    }
    
    valor = maquina.getStaticFieldVal(classIndex , field_index);
    
    if(type[0] == 'J' || type[0] == 'D') {
        maquina.current_frame->push2(valor);
    } else {
        maquina.current_frame->push(valor);
    }
    
    maquina.current_frame->pc++;
}

static void op_putstatic(Frame *pFrame) {
    uint8_t index_1, index_2;
    uint16_t indice, nameTypeIndex;
    uint64_t classIndexTemp;
    int32_t classIndex, field_index;
    uint64_t valor,valor2;
    char *className, *name, *type;
    
    index_1 = (uint8_t) maquina.current_frame->code_attr->code[++(maquina.current_frame->pc)];
    index_2 = (uint8_t) maquina.current_frame->code_attr->code[++(maquina.current_frame->pc)];
    indice = ((uint16_t)index_1 << 8) |(uint16_t)index_2;
    
    if (!indice) error(E_NOTVALID_CP_INDEX);
    
    classIndexTemp = maquina.current_frame->runtime_constant_pool->constants[indice-1].type.FieldRef.classIndex;
    className = maquina.current_frame->runtime_constant_pool->getUtf8String(maquina.current_frame->runtime_constant_pool, maquina.current_frame->runtime_constant_pool->constants[classIndexTemp-1].type.Class.nameIndex);
    
    nameTypeIndex = maquina.current_frame->runtime_constant_pool->constants[indice-1].type.FieldRef.nameTypeIndex;
    name = maquina.current_frame->runtime_constant_pool->getUtf8String(maquina.current_frame->runtime_constant_pool, maquina.current_frame->runtime_constant_pool->constants[nameTypeIndex-1].type.NameType.nameIndex);
    type = maquina.current_frame->runtime_constant_pool->getUtf8String(maquina.current_frame->runtime_constant_pool, maquina.current_frame->runtime_constant_pool->constants[nameTypeIndex-1].type.NameType.descriptorIndex);
    
    while((field_index = maquina.retrieveFieldIndex(className, name, strlen(name), type, strlen(type))) == -1) {
        className = _MCLASS.getParentName(maquina.getClassByName(className));
    }
    
    classIndex = maquina.loadClass(className);
    
    if(type[0] == 'J' || type[0] == 'D') {
        valor  = maquina.current_frame->pop();
        valor2 = maquina.current_frame->pop();
        valor = valor | (valor2 << 32);
    } else {
        valor = maquina.current_frame->pop();
    }
    
    maquina.setStaticFieldVal(classIndex , field_index, valor);
    maquina.current_frame->pc++;
}


static void op_getfield(Frame *pFrame) {
    uint8_t low, high;
    uint64_t indice;
    int64_t classIndex, field_index, aux;
    uint16_t nameTypeIndex;
    char *className, *name, *type;
    struct _object *objeto = NULL;
    uint64_t aux2;
    
    high = maquina.current_frame->code_attr->code[++(maquina.current_frame->pc)];
    low = maquina.current_frame->code_attr->code[++(maquina.current_frame->pc)];
    
    indice = high;
    indice <<= 8;
    indice = indice | low;
    
    if (!indice) error(E_NOTVALID_CP_INDEX);
    
    classIndex = maquina.current_frame->runtime_constant_pool->constants[indice-1].type.FieldRef.classIndex;
    className = maquina.current_frame->runtime_constant_pool->getUtf8String(maquina.current_frame->runtime_constant_pool, maquina.current_frame->runtime_constant_pool->constants[classIndex-1].type.Class.nameIndex);
    
    
    nameTypeIndex = maquina.current_frame->runtime_constant_pool->constants[indice-1].type.FieldRef.nameTypeIndex;
    name = maquina.current_frame->runtime_constant_pool->getUtf8String(maquina.current_frame->runtime_constant_pool, maquina.current_frame->runtime_constant_pool->constants[nameTypeIndex-1].type.NameType.nameIndex);
    type = maquina.current_frame->runtime_constant_pool->getUtf8String(maquina.current_frame->runtime_constant_pool, maquina.current_frame->runtime_constant_pool->constants[nameTypeIndex-1].type.NameType.descriptorIndex);
    
    
    while((field_index = maquina.retrieveFieldIndex(className, name, strlen(name), type, strlen(type))) == -1) {
        className = _MCLASS.getParentName(maquina.getClassByName(className));
    }
    
    aux = maquina.current_frame->pop();
    memcpy(&objeto, &aux, sizeof(uint64_t));
    
    aux2 = maquina.getObjectField(objeto, field_index);
    
    if(type[0] == 'J' || type[0] == 'D') {
        maquina.current_frame->push2(aux2);
    } else {
        maquina.current_frame->push(aux2);
    }
    
    maquina.current_frame->pc++;
}

static void op_putfield(Frame *pFrame) {
    
    uint8_t low, high;
    uint64_t indice,aux;
    int64_t classIndex, field_index, val_1;
    uint16_t nameTypeIndex;
    char *className, *name, *type;
    struct _object *objeto = NULL;
    uint64_t valor,valor2;
    
    high = maquina.current_frame->code_attr->code[++(maquina.current_frame->pc)];
    low = maquina.current_frame->code_attr->code[++(maquina.current_frame->pc)];
    
    indice = high;
    indice <<= 8;
    indice = indice | low;
    
    if (!indice) error(E_NOTVALID_CP_INDEX);
    
    classIndex = maquina.current_frame->runtime_constant_pool->constants[indice-1].type.FieldRef.classIndex;
    className = maquina.current_frame->runtime_constant_pool->getUtf8String(maquina.current_frame->runtime_constant_pool, maquina.current_frame->runtime_constant_pool->constants[classIndex-1].type.Class.nameIndex);
    
    nameTypeIndex = maquina.current_frame->runtime_constant_pool->constants[indice-1].type.FieldRef.nameTypeIndex;
    name = maquina.current_frame->runtime_constant_pool->getUtf8String(maquina.current_frame->runtime_constant_pool, maquina.current_frame->runtime_constant_pool->constants[nameTypeIndex-1].type.NameType.nameIndex);
    type = maquina.current_frame->runtime_constant_pool->getUtf8String(maquina.current_frame->runtime_constant_pool, maquina.current_frame->runtime_constant_pool->constants[nameTypeIndex-1].type.NameType.descriptorIndex);
    
    while((field_index = maquina.retrieveFieldIndex(className, name, strlen(name), type, strlen(type))) == -1) {
        className = _MCLASS.getParentName(maquina.getClassByName(className));
    }
    
    if(type[0] == 'J' || type[0] == 'D') {
        valor  = maquina.current_frame->pop();
        valor2 = maquina.current_frame->pop();
        valor = valor | (valor2 << 32);
        
        aux = maquina.current_frame->pop();
        memcpy(&objeto, &aux, sizeof(uint64_t));
        maquina.setObjectField(objeto, field_index, valor);
        
    } else {
        val_1 = maquina.current_frame->pop();
        aux = maquina.current_frame->pop();
        
        memcpy(&objeto, &aux, sizeof(uint64_t));
        maquina.setObjectField(objeto, field_index, val_1);
    }
    
    maquina.current_frame->pc++;
}

static void op_invokevirtual(Frame *pFrame) {
    uint64_t indice = 0, valorHigh = 0, valorLow = 0, vU8 = 0, array_ref = 0;
    uint8_t low = 0, high = 0;
    int64_t numParams = 0, i = 0, j = 0;
    int64_t classIndex = 0, classIndexTemp = 0;
    uint16_t nameTypeIndex = 0, methodNameIndex = 0, methodDescriptorIndex = 0;
    char *className = NULL, *methodName = NULL, *methodDesc = NULL;
    uint64_t *fieldsTemp = NULL;
    float vfloat = 0;
    CLASS *class = NULL;
    struct _method_info  *method = NULL;
    
    high = maquina.current_frame->code_attr->code[++(maquina.current_frame->pc)];
    low = maquina.current_frame->code_attr->code[++(maquina.current_frame->pc)];
    
    indice = high;
    indice <<= 8;
    indice = indice | low;
    
    if (!indice) error(E_NOTVALID_CP_INDEX);
    
    classIndexTemp = maquina.current_frame->runtime_constant_pool->constants[indice-1].type.MethodRef.classIndex;
    className = maquina.getNameConstants(maquina.current_frame->current_class, maquina.current_frame->runtime_constant_pool->constants[classIndexTemp-1].type.Class.nameIndex);
    nameTypeIndex = maquina.current_frame->runtime_constant_pool->constants[indice-1].type.MethodRef.nameTypeIndex;
    
    methodNameIndex = maquina.current_frame->runtime_constant_pool->constants[nameTypeIndex-1].type.NameType.nameIndex;
    methodDescriptorIndex = maquina.current_frame->runtime_constant_pool->constants[nameTypeIndex-1].type.NameType.descriptorIndex;
    methodDesc = maquina.getNameConstants(maquina.current_frame->current_class, methodDescriptorIndex);
    methodName = maquina.getNameConstants(maquina.current_frame->current_class, methodNameIndex);
    
    if((strcmp(className, "java/io/PrintStream") == 0) && ((strcmp(methodName,"println") == 0) ||(strcmp(methodName,"print") == 0))){
        
        //Quando tem que imprimir long
        if(strstr(methodDesc, "J") != NULL){
            valorLow = maquina.current_frame->pop();
            valorHigh = maquina.current_frame->pop();
            
            printf("%ld",(long)getLong(valorHigh,valorLow));
            
            //Quando tem que imprimir double
        } else if(strstr(methodDesc, "D") != NULL) {
            valorLow = maquina.current_frame->pop();
            valorHigh = maquina.current_frame->pop();
            
            printf("%f", (double)getDouble(valorHigh,valorLow));
            
            //Quando tem que imprimir boolean
        } else if(strstr(methodDesc, "Z") != NULL) {
            
            if(!maquina.current_frame->pop()) {
                printf("false");
            } else {
                printf("true");
            }
            
            //Quando tem que imprimir char
        } else if(strstr(methodDesc, "C") != NULL) {
            
            //array
            if(strstr(methodDesc, "[C") != NULL){
                array_ref = maquina.current_frame->pop();
                for(i = 0; i < maquina.heap->array_count; i++){
                    if(!memcmp(&maquina.heap->arrays[i], &array_ref, sizeof(uint64_t)))
                        break;
                }
                for(j = 0; j < maquina.heap->array_count; j++){
                    printf("%"PRIi16,(int16_t)(array_ref +i));
                }
                //CHAR
            } else {
                printf("%c",(int16_t)maquina.current_frame->pop());
            }
            
            //Quando tem que imprimir inteiro
        }else if(strstr(methodDesc, "I") != NULL) {
            printf("%d",(int)maquina.current_frame->pop());
            
            //Quando tem que imprimir float
        }else if(strstr(methodDesc, "F") != NULL) {
            vU8 = maquina.current_frame->pop();
            memcpy(&vfloat, &vU8, sizeof(uint32_t));
            printf("%f", vfloat);
            
            //Quando tem que imprimir string
        }else if(strstr(methodDesc, "Ljava/lang/String") != NULL) {
            vU8 = maquina.current_frame->pop();
            printf("%s",maquina.current_frame->current_class->constant_pool->constants[vU8-1].type.Utf8.bytes);
            
            //OBJECT
        }else if(strstr(methodDesc, "Ljava/lang/Object") != NULL) {
            void* aux = NULL;
            vU8 = maquina.current_frame->pop();
            memcpy(&aux, &vU8, sizeof(uint64_t));
            printf("%p",aux);
        }
        
        if(strcmp(methodName,"println") == 0) {
            printf("\n");
        }
        
        maquina.current_frame->pop();
    } else {
        classIndex = maquina.loadClass(className);
        class = maquina.method_area->classes[classIndex];
        
        while(class != NULL && (method = maquina.getMethodByNameDesc(class, maquina.current_frame->current_class, nameTypeIndex)) == NULL) {
            className = _MCLASS.getParentName(class);
            classIndex = maquina.loadClass(className);
            class = maquina.method_area->classes[classIndex];
        }
        
        if(class == NULL) {
            printf("Erro: Metodo nao encontrando.\n");
            exit(1);
        }
        
        numParams = maquina.getNumParameters(class, method);
        fieldsTemp = calloc(sizeof(uint64_t),numParams+1);
        for(i = numParams; i > 0; i--) {
            fieldsTemp[i] = maquina.current_frame->pop();
        }
        
        if(((method->access_flags) & mask_native) || strcmp("println", maquina.getNameConstants(class, method->name_index)) == 0) {
            maquina.current_frame->pop();
            
            // implementar aqui codigo para lidar com metodos nativos
            
        } else {
            uint64_t objectref = maquina.current_frame->pop();
            maquina.construirFrame(class, method);
            for(i = numParams; i > 0; i--) {
                maquina.current_frame->local_variables[i] = fieldsTemp[i];
            }
            maquina.current_frame->local_variables[0] = objectref;
            maquina.execute();
        }
    }
    
    maquina.current_frame->pc++;
}

static void op_invokespecial(Frame *pFrame) {
    uint64_t indice, *fieldsTemp;;
    uint8_t low, high;
    int64_t i, classIndex, classIndexTemp;
    uint16_t nameTypeIndex;
    char *className;
    CLASS *class;
    struct _method_info *method;
    int numParams;
    
    high = maquina.current_frame->code_attr->code[++(maquina.current_frame->pc)];
    low = maquina.current_frame->code_attr->code[++(maquina.current_frame->pc)];
    
    indice = high;
    indice <<= 8;
    indice = indice | low;
    
    if (!indice) error(E_NOTVALID_CP_INDEX);
    
    classIndexTemp = maquina.current_frame->runtime_constant_pool->constants[indice-1].type.MethodRef.classIndex;
    className = maquina.getNameConstants(maquina.current_frame->current_class, maquina.current_frame->runtime_constant_pool->constants[classIndexTemp-1].type.Class.nameIndex);
    
    nameTypeIndex = maquina.current_frame->runtime_constant_pool->constants[indice-1].type.MethodRef.nameTypeIndex;
    
    classIndex = maquina.loadClass(className);
    class = maquina.method_area->classes[classIndex];
    
    while(class != NULL && (method = maquina.getMethodByNameDesc(class, maquina.current_frame->current_class, nameTypeIndex)) == NULL) {
        className = _MCLASS.getParentName(class);
        classIndex = maquina.loadClass(className);
        class = maquina.method_area->classes[classIndex];
    }
    
    if(class == NULL) {
        printf("Metodo nao foi encontrando, veja.\n");
    }
    
    numParams = maquina.getNumParameters(class , method);
    
    
    fieldsTemp = calloc(sizeof(uint64_t),numParams+1);
    for(i = numParams; i > 0; i--) {
        fieldsTemp[i] = maquina.current_frame->pop();
    }
    
    if((method->access_flags) & mask_native) {
        maquina.current_frame->pop();
        
        // implementar aqui codigo para lidar com metodos nativos
        
    } else {
        uint64_t objectref = maquina.current_frame->pop();
        maquina.construirFrame(class, method);
        
        for(i = numParams; i > 0; i--) {
            maquina.current_frame->local_variables[i] = fieldsTemp[i];
        }
        
        maquina.current_frame->local_variables[0] = objectref;
        maquina.execute();
    }
    
    maquina.current_frame->pc++;
    
}

static void op_invokestatic(Frame *pFrame) {
    // printf("\n\t\t\t\tentrou invokestatic: %p", maquina.current_frame);
    uint64_t indice, *fieldsTemp;
    uint8_t low, high;
    int64_t numParams, i, classIndex, classIndexTemp;
    uint16_t nameTypeIndex;
    char *className;
    CLASS *class;
    struct _method_info *method;
    
    high = maquina.current_frame->code_attr->code[++(maquina.current_frame->pc)];
    low = maquina.current_frame->code_attr->code[++(maquina.current_frame->pc)];
    
    indice = high;
    indice <<= 8;
    indice = indice | low;
    
    if (!indice) error(E_NOTVALID_CP_INDEX);
    
    classIndexTemp = maquina.current_frame->runtime_constant_pool->constants[indice-1].type.MethodRef.classIndex;
    className = maquina.getNameConstants(maquina.current_frame->current_class, maquina.current_frame->runtime_constant_pool->constants[classIndexTemp-1].type.Class.nameIndex);
    nameTypeIndex = maquina.current_frame->runtime_constant_pool->constants[indice-1].type.MethodRef.nameTypeIndex;
    
    classIndex = maquina.loadClass(className);
    class = maquina.method_area->classes[classIndex];
    
    method = maquina.getMethodByNameDesc(class, maquina.current_frame->current_class, nameTypeIndex);
    numParams = maquina.getNumParameters(class , method);
    fieldsTemp = calloc(sizeof(uint64_t),numParams+1);
    for(i = numParams - 1; i >= 0; i--) {
        fieldsTemp[i] = maquina.current_frame->pop();
    }
    
    if((method->access_flags) & mask_native) {
        
        // implementar aqui codigo para lidar com metodos nativos
        
    } else {
        maquina.construirFrame(class, method);
        for(i = numParams - 1; i >= 0; i--) {
            maquina.current_frame->local_variables[i] = fieldsTemp[i];
        }
        maquina.execute();
    }
    maquina.current_frame->pc++;
}

static void op_invokeinterface(Frame *pFrame) {
    uint64_t indice, *fieldsTemp;
    uint8_t low, high, args_count;
    int64_t classIndex, classIndexTemp, i;
    uint16_t nameTypeIndex;
    char *className;
    CLASS *class;
    struct _method_info *method;
    
    high = maquina.current_frame->code_attr->code[++(maquina.current_frame->pc)];
    low = maquina.current_frame->code_attr->code[++(maquina.current_frame->pc)];
    
    indice = high;
    indice <<= 8;
    indice = indice | low;
    
    if (!indice) error(E_NOTVALID_CP_INDEX);
    
    args_count = maquina.current_frame->code_attr->code[++(maquina.current_frame->pc)];
    maquina.current_frame->pc++;
    
    fieldsTemp = calloc(sizeof(uint64_t),args_count+1);
    
    for(i = args_count; i > 0; i--) {
        fieldsTemp[i] = maquina.current_frame->pop();
    }
    
    classIndexTemp = maquina.current_frame->runtime_constant_pool->constants[indice-1].type.MethodRef.classIndex;
    className = maquina.getNameConstants(maquina.current_frame->current_class, maquina.current_frame->runtime_constant_pool->constants[classIndexTemp-1].type.Class.nameIndex);
    nameTypeIndex = maquina.current_frame->runtime_constant_pool->constants[indice-1].type.MethodRef.nameTypeIndex;
    
    classIndex = maquina.loadClass(className);
    class = maquina.method_area->classes[classIndex];
    
    while(class != NULL && (method = maquina.getMethodByNameDesc(class, maquina.current_frame->current_class, nameTypeIndex)) == NULL) {
        className = _MCLASS.getParentName(class);
        classIndex = maquina.loadClass(className);
        class = maquina.method_area->classes[classIndex];
    }
    
    if(class == NULL) {
        printf("Metodo nao encontrado.\n");
    }
    
    uint64_t objectref = maquina.current_frame->pop();
    maquina.construirFrame(class, method);
    for(i = args_count; i > 0; i--) {
        maquina.current_frame->local_variables[i] = fieldsTemp[i];
    }
    maquina.current_frame->local_variables[0] = objectref;
    maquina.execute();
    maquina.current_frame->pc++;
    
}

static void op_new(Frame *pFrame) {
    // printf("\n\t\t\tentrou _new");
    uint8_t low, high;
    uint64_t indice;
    char *className;	
    int64_t classIndex;
    
    CLASS *class;
    struct _object *objeto;
    
    high = maquina.current_frame->code_attr->code[++(maquina.current_frame->pc)];
    low = maquina.current_frame->code_attr->code[++(maquina.current_frame->pc)];
    
    indice = high;
    indice <<= 8;
    indice |= low;
    
    
    if (!indice) error(E_NOTVALID_CP_INDEX);
    className = _MCONSTANTP.getClassName(maquina.current_frame->runtime_constant_pool, indice);
    
    classIndex = maquina.loadClass(className);
    
    class = maquina.method_area->classes[classIndex];
    
    objeto = maquina.heap->newObject(class);
    
    
    maquina.current_frame->push((uint64_t)(intptr_t)objeto);
    maquina.current_frame->pc++;
}

static void op_newarray(Frame *pFrame) {
    int count;
    uint8_t type;
    count = maquina.current_frame->pop();
    maquina.current_frame->pc++;
    
    type = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)];
    if (count < 0) error(E_NEG_ARR_SIZE);
    
    maquina.current_frame->push((uint64_t)(intptr_t)maquina.heap->newArray(count,type));
    maquina.current_frame->pc++;
}

static void op_anewarray(Frame *pFrame) {
    int count = maquina.current_frame->pop();
    if (count < 0) error(E_NEG_ARR_SIZE);
    
    uint8_t index_byte1 = maquina.current_frame->code_attr->code[++maquina.current_frame->pc];
    uint8_t index_byte2 = maquina.current_frame->code_attr->code[++maquina.current_frame->pc];
    uint16_t indice = index_byte1; indice = indice << 8 | index_byte2;
    
    char* className = _MCONSTANTP.getClassName(maquina.current_frame->runtime_constant_pool, indice);
    
    void* pointer = maquina.heap->newRefArray(count,className);
    
    maquina.current_frame->push((uint64_t)(intptr_t)pointer);
    maquina.current_frame->pc++;
}

static void op_arraylength(Frame *pFrame) {
    uint64_t reference = maquina.current_frame->pop();
    if (reference == 0) error(E_NULL_POINTER);
    
    for(int i=0;i < maquina.heap->array_count; i++){
        
        // push somente a quantidade do array correto
        if(!memcmp(&maquina.heap->arrays[i], &reference, sizeof(struct _array*))) {
            maquina.current_frame->push(maquina.heap->arrays[i]->quantidade);
            maquina.current_frame->pc++;
            return;
        }
    }
    
    error(E_ARR_NOT_FOUND);
}

static void op_athrow(Frame *pFrame) {
    maquina.current_frame->pc++;
}

static void op_checkcast(Frame *pFrame) {
    struct _object *reference;
    uint16_t indice;
    
    maquina.current_frame->pc++;
    indice = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)];
    indice = indice << 8;
    maquina.current_frame->pc++;
    indice = indice | maquina.current_frame->code_attr->code[(maquina.current_frame->pc)];
    
    reference = (struct _object *)(intptr_t)maquina.current_frame->pop();
    
    char* className1 = maquina.current_frame->current_class->getName(maquina.current_frame->current_class);
    char* className2 = _MCONSTANTP.getClassName(reference->class->constant_pool,indice);
    
    if(reference == NULL) {
        printf("Erro: Null Reference\n");
    }
    if(strcmp(className1, className2) == 0) {
        printf(" Erro: Wrong Typt Object\n");
    }
    maquina.current_frame->push((uint64_t)(intptr_t)reference);
    maquina.current_frame->pc++;
    
}

static void op_instanceof(Frame *pFrame) {
    
    struct _object *reference;
    uint16_t indice;
    
    maquina.current_frame->pc++;
    indice = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)];
    indice = indice << 8;
    maquina.current_frame->pc++;
    indice = indice | maquina.current_frame->code_attr->code[(maquina.current_frame->pc)];
    reference = (struct _object *)(intptr_t)maquina.current_frame->pop();
    
    if(reference == NULL) {
        printf("Erro: Null Reference\n");
    }
    
    char* className1 = maquina.current_frame->current_class->getName(maquina.current_frame->current_class);
    char* className2 = _MCONSTANTP.getClassName(reference->class->constant_pool,indice);
    
    if(strcmp(className1, className2) == 0) {
        maquina.current_frame->push(1);
        maquina.current_frame->pc++;
        return;
    }
    maquina.current_frame->push(0);
    maquina.current_frame->pc++;
}

static void op_monitorenter(Frame *pFrame) {
    printf("monitorenter: Not supported instruction");
    exit(1);
}

static void op_monitorexit(Frame *pFrame) {
    printf("monitorexit: Not supported instruction");
    exit(1);
}

static void op_wide(Frame *pFrame) {
    WIDE = 1;
    maquina.current_frame->pc++;
}

static void op_multianewarray(Frame *pFrame) {
    // error(E_NOT_SUPPORTED_INSTRUCTION);
    uint16_t indice = maquina.current_frame->code_attr->code[++maquina.current_frame->pc];
    indice = indice << 8 | maquina.current_frame->code_attr->code[++maquina.current_frame->pc];
    int dimensionCount = maquina.current_frame->code_attr->code[++maquina.current_frame->pc];
    char* marrayInfo = _MCONSTANTP.getClassName(maquina.current_frame->runtime_constant_pool, indice);
    
    // multianewarray apenas para arrays de dimensão >= 2
    if (dimensionCount < 1 || marrayInfo == NULL || (marrayInfo[0] != '[' && marrayInfo[1] != '[')) error(E_NOT_VALID_MARRAY_INFO);
    
    int* qtdByDimension = (int*)malloc(dimensionCount*sizeof(int));
    
    for (int i = 0; i < dimensionCount; i++) {
        int aux = maquina.current_frame->pop();
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
            char* className = (char*)malloc(strlen(marrayInfo)*sizeof(char));
            for (int i = dimensionCount+1; i < strlen(marrayInfo); i++) {
                className[i - dimensionCount -1] = marrayInfo[i];
                className[i - dimensionCount] = '\0';
            }
            maquina.loadClass(className);
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
    
    void *pointer = maquina.heap->newMultiArray(0, dimensionCount, qtdByDimension, tipo);
    maquina.current_frame->push((uint64_t)(intptr_t)pointer);
    maquina.current_frame->pc++;
}

static void op_ifnull(Frame *pFrame) {
    uint8_t bb1, bb2;
    int64_t auxiliar_32;
    uint64_t offset;
    
    bb1 = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+1];
    bb2 = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+2];
    auxiliar_32 = (signed) maquina.current_frame->pop();
    
    if(auxiliar_32 == 0) {
        uint64_t value;
        value = bb1;
        value <<= 8;
        value |= bb2;
        offset = value;		
        maquina.current_frame->pc += offset;
    } else {
        maquina.current_frame->pc += 3;
    }
    
}

static void op_ifnonnull(Frame *pFrame) {
    uint8_t bb1, bb2;
    int64_t auxiliar_32;
    int16_t offset;
    
    bb1 = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+1];
    bb2 = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+2];
    auxiliar_32 = (signed) maquina.current_frame->pop();
    
    if(auxiliar_32 != 0){
        uint64_t value;
        value = bb1;
        value <<= 8;
        value |= bb2;
        offset = value;
        maquina.current_frame->pc += offset;
    }else{
        maquina.current_frame->pc += 3;
    }
    
}

static void op_goto_w(Frame *pFrame) {
    uint64_t bb1, bb2, bb3, bb4;
    int64_t offset;
    
    bb1 = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+1];
    bb2 = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+2];
    bb3 = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+3];
    bb4 = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+4];
    
    offset = (int64_t)(((bb1 & 0xFF)<<24) |((bb2 & 0xFF)<<16) |((bb3 & 0xFF)<<8) |(bb4));
    maquina.current_frame->pc += offset;
}

static void op_jsr_w(Frame *pFrame) {
    uint64_t bb1, bb2, bb3, bb4;
    int64_t offset;
    
    maquina.current_frame->push((maquina.current_frame->pc)+5);
    
    bb1 = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+1];
    bb2 = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+2];
    bb3 = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+3];
    bb4 = maquina.current_frame->code_attr->code[(maquina.current_frame->pc)+4];
    
    offset = (int64_t)(((bb1 & 0xFF)<<24) |((bb2 & 0xFF)<<16) |((bb3 & 0xFF)<<8) |(bb4));
    maquina.current_frame->pc += offset;
}
