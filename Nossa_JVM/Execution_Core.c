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
            case op_iconst_m1:
            case op_iconst_0:
            case op_iconst_1:
            case op_iconst_2:
            case op_iconst_3:
            case op_iconst_4:
            case op_iconst_5:
                pFrame->sp++;
                pFrame->stack[pFrame->sp] = code_iterator[pFrame->pc] - op_iconst_0;
                pFrame->pc++;
                break;
                
            case op_aconst_null:
                pFrame->sp++;
                pFrame->stack[pFrame->sp] = 0;
                pFrame->pc++;
                break;
                
            case op_lconst_0:// 9 /*(0x9)*/
            case op_lconst_1:// 10 /*(0xa)*/
                pFrame->sp++;
                pFrame->stack[pFrame->sp] = 0;
                pFrame->sp++;
                pFrame->stack[pFrame->sp] = code_iterator[pFrame->pc] - op_lconst_0;
                pFrame->pc++;
                break;
                
            case op_bipush:// 16 /*(0x10)*/
                pFrame->sp++;
                pFrame->stack[pFrame->sp] = code_iterator[pFrame->pc+1];
                pFrame->pc += 2;
                break;
            case op_sipush:// 17 /*(0x11)*/
                pFrame->sp++;
                pFrame->stack[pFrame->sp] = getu2(&code_iterator[pFrame->pc+1]);
                pFrame->pc += 3;
                break;
                
            case op_ldc: //Push item from constant pool
                pFrame->sp++;
                pFrame->stack[pFrame->sp] = LoadConstant(pFrame->pClass, code_iterator[pFrame->pc + 1]);
                pFrame->pc += 2;
                break;
                
            case op_ldc2_w:// 20 /*(0x14)*/
                i = getu2(&code_iterator[pFrame->pc + 1]);
                pFrame->sp++;
                pFrame->stack[pFrame->sp] = pFrame->pClass->constant_pool[i - 1].info.CONSTANT_LongDouble_info.high_bytes;
                pFrame->sp++;
                pFrame->stack[pFrame->sp] = pFrame->pClass->constant_pool[i - 1].info.CONSTANT_LongDouble_info.low_bytes;
                pFrame->pc += 3;
                break;
                
                //Instructions that load a local variable onto the stack
            case op_aload:// 25 /*(0x19)*/
                pFrame->sp++;
                pFrame->stack[pFrame->sp] = pFrame->local[(u1) code_iterator[pFrame->pc+1]];
                pFrame->pc += 2;
                break;
                
            case op_iload:// 21 /*(0x15)*/
                pFrame->sp++;
                pFrame->stack[pFrame->sp] = pFrame->local[(u1) code_iterator[pFrame->pc+1]];
                pFrame->pc += 2;
                break;
            case op_iload_0: //26 Load int from local variable 0
            case op_iload_1: //27 Load int from local variable 1
            case op_iload_2: //28 Load int from local variable 2
            case op_iload_3: //29 Load int from local variable 3
                pFrame->sp++;
                pFrame->stack[pFrame->sp] = pFrame->local[(u1) code_iterator[pFrame->pc] - op_iload_0];
                pFrame->pc++;
                break;
                
                
            case op_lload:// 22 /*(0x16)*/
                
                break;
            case op_lload_0:// 30 /*(0x1e) */
            case op_lload_1:// 31 /*(0x1f) */
            case op_lload_2:// 32 /*(0x20) */
            case op_lload_3:// 33 /*(0x21) */
                pFrame->sp++;
                pFrame->stack[pFrame->sp] = pFrame->local[(u1) code_iterator[pFrame->pc] - op_lload_0];
                pFrame->sp++;
                pFrame->stack[pFrame->sp] = pFrame->local[(u1)code_iterator[pFrame->pc] - op_lload_0 + 1];
                pFrame->pc++;
                break;
                
            case op_fload_0: // 34 /*(0x22)*/
            case op_fload_1: // 35 /*(0x23)*/
            case op_fload_2: // 36 /*(0x24)*/
            case op_fload_3: // 37 /*(0x25)*/
                pFrame->sp++;
                pFrame->stack[pFrame->sp] = pFrame->local[(u1) code_iterator[pFrame->pc] - op_fload_0];
                pFrame->pc++;
                break;
                
            case op_aload_0:  //42 Load reference from local variable 0
            case op_aload_1:  //Load reference from local variable 1
            case op_aload_2:  //Load reference from local variable 2
            case op_aload_3:  //Load reference from local variable 3
                pFrame->sp++;
                pFrame->stack[pFrame->sp] = pFrame->local[(u1) code_iterator[pFrame->pc] - op_aload_0];
                pFrame->pc++;
                break;
                
//            case op_iaload:// 46 /*(0x2e)*/Load int from array
//                //..., arrayref, index  => ..., value
//                pFrame->stack[pFrame->sp - 1] = getArrayVariable(pFrame->stack[pFrame->sp - 1], pFrame->stack[pFrame->sp], 2);
//                pFrame->sp--;
//                pFrame->pc++;
//                break;
////            case op_aaload://50
////                //..., arrayref, index  ..., value
////                pFrame->stack[pFrame->sp - 1] = pFrame->stack[pFrame->sp - 1]->arrayList[pFrame->stack[pFrame->sp]];
////                pFrame->sp--;
////                pFrame->pc++;
////                break;
//                //Instructions that store a value from the stack into a local variable
//            case op_astore:// 58 (0x3a)
//                pFrame->local[(u1) code_iterator[pFrame->pc+1]] = pFrame->stack[pFrame->sp];
//                pFrame->sp--;
//                pFrame->pc+=2;
//                break;
//                
            case op_istore:// 54 /*(0x36)*/
                pFrame->local[(u1) code_iterator[pFrame->pc+1]] = pFrame->stack[pFrame->sp];
                pFrame->sp--;
                pFrame->pc+=2;
                break;
            case op_istore_0: // 59 /*(0x3b)*/
            case op_istore_1: // 60 /*(0x3c) */
            case op_istore_2: // 61 /*(0x3d) */
            case op_istore_3: // 62 /*(0x3e)*/
                pFrame->local[(u1) code_iterator[pFrame->pc] - op_istore_0] = pFrame->stack[pFrame->sp];
                pFrame->sp--;
                pFrame->pc++;
                break;
                
//            case op_lstore_0: // 63 /*(0x3f) */
//            case op_lstore_1: // 64 /*(0x40) */
//            case op_lstore_2: // 65 /*(0x41) */
//            case op_lstore_3: // 66 /*(0x42) */
//                pFrame->local[(u1) code_iterator[pFrame->pc] - op_lstore_0 + 1] = pFrame->stack[pFrame->sp];
//                pFrame->sp--;
//                pFrame->local[(u1) code_iterator[pFrame->pc] - op_lstore_0] = pFrame->stack[pFrame->sp];
//                pFrame->sp--;
//                pFrame->pc++;
//                break;
//                
//            case op_fstore_0:
//            case op_fstore_1:
//            case op_fstore_2:
//            case op_fstore_3:
//                pFrame->local[(u1)code_iterator[pFrame->pc] - op_fstore_0] = pFrame->stack[pFrame->sp];
//                pFrame->sp--;
//                pFrame->pc++;
//                break;
//                
//            case op_astore_0:// 75 /*(0x4b) Store reference into local variable 0*/
//            case op_astore_1:// 76 /*(0x4c) */
//            case op_astore_2:// 77 /*(0x4d) */
//            case op_astore_3:// 78 /*(0x4e)*/
//                pFrame->local[(u1) code_iterator[pFrame->pc] - op_astore_0] = pFrame->stack[pFrame->sp];
//                pFrame->sp--;
//                pFrame->pc++;
//                break;
//                
//            case op_iastore:// 79 /*(0x4f)*/
//            case op_aastore: // 83 - both seems same (TODO: Check it)
//                pFrame->stack[pFrame->sp-2]->arrrayList[pFrame->stack[pFrame->sp-1]] = pFrame->stack[pFrame->sp];
//                pFrame->sp-=3;
//                pFrame->pc++;
//                break;
                
                //Generic (typeless) stack operations
                
            case op_dup:// 89 /*(0x59)*/
                pFrame->stack[pFrame->sp+1] = pFrame->stack[pFrame->sp];
                pFrame->sp++;
                pFrame->pc++;
                break;
                
//                //Type Conversion
//                
//                //Integer Arithmetic
                
            case op_iadd: //96
                pFrame->stack[pFrame->sp-1] = pFrame->stack[pFrame->sp-1] + pFrame->stack[pFrame->sp];
                pFrame->sp--;
                pFrame->pc++;
                break;
            case op_ladd:// 97 /*(0x61)*/
                longVal = (i8)(((i8)pFrame->stack[pFrame->sp-3]<<32) | (i8)pFrame->stack[pFrame->sp-2])+(i8)(((i8)pFrame->stack[pFrame->sp-1]<<32) | (i8)pFrame->stack[pFrame->sp]);
                pFrame->stack[pFrame->sp-3] = HIINT64(longVal);
                pFrame->stack[pFrame->sp-2] = LOINT64(longVal);
                pFrame->sp -= 2;
                pFrame->pc++;
                break;
            case op_isub: //100
                pFrame->stack[pFrame->sp-1] = pFrame->stack[pFrame->sp-1] - pFrame->stack[pFrame->sp];
                pFrame->sp--;
                pFrame->pc++;
                break;
            case op_imul://104
                pFrame->stack[pFrame->sp-1] = pFrame->stack[pFrame->sp-1] * pFrame->stack[pFrame->sp];
                pFrame->sp--;
                pFrame->pc++;
                break;
            case op_idiv://108
                pFrame->stack[pFrame->sp-1] = pFrame->stack[pFrame->sp-1] / pFrame->stack[pFrame->sp];
                pFrame->sp--;
                pFrame->pc++;
                break;
            case op_iinc:// 132 /*(0x84)*/ Increment local variable by constant
                pFrame->stack[(u1)code_iterator[pFrame->pc+1]] += (char)code_iterator[pFrame->pc+2];
                pFrame->pc+=3;
                break;
                //////////////////// Logic ///////////////////
                
                //Shift operations
                
                //Bitwise boolean operations
                
                //Floating Point Arithmetic
            case op_getstatic:
                i = getu2(&code_iterator[pFrame->pc+1]);
                field_name = getFieldName(i, pFrame->pClass->constant_pool);
                field_index = getFieldIndex(field_name, pFrame->pClass->static_values, pFrame->pClass->static_values_size);
                pFrame->sp++;
                pFrame->stack[pFrame->sp] = field_index;
                pFrame->pc += 3;
                break;
                
            case op_putstatic:
                i = getu2(&code_iterator[pFrame->pc+1]);
                field_name = getFieldName(i, pFrame->pClass->constant_pool);
                fv = getFieldValue(field_name, pFrame->pClass->static_values, pFrame->pClass->static_values_size);
                if (strcmp(fv->descriptor,"Ljava/lang/String;") == 0) {
                    fv->info.UTF8.bytes = pFrame->stack[pFrame->sp];
                    pFrame->sp--;
                }
                else {
                    if (strcmp(fv->descriptor,"I") == 0 || strcmp(fv->descriptor,"F") == 0) {
                        fv->info.I4.value = pFrame->stack[pFrame->sp];
                        pFrame->sp--;
                    }
                    else {
                        if (strcmp(fv->descriptor,"D") == 0 || strcmp(fv->descriptor,"J") == 0) {
                            fv->info.U8.low = pFrame->stack[pFrame->sp];
                            pFrame->sp--;
                            fv->info.U8.high = pFrame->stack[pFrame->sp];
                            pFrame->sp--;
                        }

                    }

                }
                pFrame->pc += 3;
                break;
                /////////////// Objects and Arrays  ////////////
                
                //Instructions that deal with objects
//                
//            case op_new:// 187 (0xbb)
//                //ExecuteNew(pFrame);
//                pFrame->pc+=3;
//                break;
//            case op_putfield: //181 (0xb5): Set field in object
//                PutField(pFrame);
//                pFrame->sp-=2;
//                pFrame->pc+=3;
//                break;
//                
//            case op_getfield: //180 (0xb4) Fetch field from object
//                GetField(pFrame);
//                pFrame->pc+=3;
//                break;
//                
//                //Instructions that deal with arrays
//                
//            case op_newarray:// 188 /*(0xbc)*/
//                ExecuteNewArray(pFrame);
//                pFrame->pc+=2;
//                break;
//                
//            case op_anewarray: //189
//                ExecuteANewArray(pFrame);
//                pFrame->pc+=3;
//                break;
//                ////////////// Control Flow /////////////////////
//                
//                //Conditional branch instructions
//                
//            case op_if_icmpeq: // 159 /*(0x9f) */
//                if(pFrame->stack[pFrame->sp -1] == pFrame->stack[pFrame->sp]) {
//                    pFrame->pc += geti2(&code_iterator[pFrame->pc+1]);
//                }
//                else {
//                    pFrame->pc+=3;
//                }
//                pFrame->sp-=2;
//                break;
//            case op_if_icmpne: //160 /*(0xa0) */
//                if(pFrame->stack[pFrame->sp -1] != pFrame->stack[pFrame->sp]) {
//                    pFrame->pc+= geti2(&code_iterator[pFrame->pc+1]);
//                }
//                else {
//                    pFrame->pc+=3;
//                }
//                pFrame->sp-=2;
//                break;
//            case op_if_icmplt: // 161 /*(0xa1) */
//                if(pFrame->stack[pFrame->sp -1] < pFrame->stack[pFrame->sp]) {
//                    pFrame->pc+= geti2(&code_iterator[pFrame->pc+1]);
//                }
//                else {
//                    pFrame->pc+=3;
//                }
//                pFrame->sp-=2;
//                break;
//            case op_if_icmpge: // 162 /*(0xa2) */
//                if(pFrame->stack[pFrame->sp -1] >= pFrame->stack[pFrame->sp]) {
//                    pFrame->pc+= geti2(&code_iterator[pFrame->pc+1]);
//                }
//                else {
//                    pFrame->pc+=3;
//                }
//                pFrame->sp-=2;
//                break;
//            case op_if_icmpgt: // 163 /*(0xa3) */
//                if(pFrame->stack[pFrame->sp -1] > pFrame->stack[pFrame->sp]) {
//                    pFrame->pc+= geti2(&code_iterator[pFrame->pc+1]);
//                }
//                else {
//                    pFrame->pc+=3;
//                }
//                pFrame->sp-=2;
//                break;
//            case op_if_icmple: // 164 /*(0xa4)*/
//                if(pFrame->stack[pFrame->sp -1] <= pFrame->stack[pFrame->sp]) {
//                    pFrame->pc+= geti2(&code_iterator[pFrame->pc+1]);
//                }
//                else {
//                    pFrame->pc+=3;
//                }
//                pFrame->sp-=2;
//                break;
//                
//            case op_ifeq:// 153 /*(0x99) */
//                if(pFrame->stack[pFrame->sp] == 0) {
//                    pFrame->pc+= geti2(&code_iterator[pFrame->pc+1]);
//                }
//                else {
//                    pFrame->pc+=3;
//                }
//                pFrame->sp--;
//                break;
//            case op_ifne:// 154 /*(0x9a) */
//                if(pFrame->stack[pFrame->sp] != 0) {
//                    pFrame->pc+= geti2(&code_iterator[pFrame->pc+1]);
//                }
//                else {
//                    pFrame->pc+=3;
//                }
//                pFrame->sp--;
//                break;
//            case op_iflt:// 155 /*(0x9b) */
//                if(pFrame->stack[pFrame->sp] < 0) {
//                    pFrame->pc+= geti2(&code_iterator[pFrame->pc+1]);
//                }
//                else {
//                    pFrame->pc+=3;
//                }
//                pFrame->sp--;
//                break;
//            case op_ifge:// 156 /*(0x9c) */
//                if(pFrame->stack[pFrame->sp] >= 0) {
//                    pFrame->pc+= geti2(&code_iterator[pFrame->pc+1]);
//                }
//                else {
//                    pFrame->pc+=3;
//                }
//                pFrame->sp--;
//                break;
//            case op_ifgt:// 157 /*(0x9d) */
//                if(pFrame->stack[pFrame->sp] > 0) {
//                    pFrame->pc+= geti2(&code_iterator[pFrame->pc+1]);
//                }
//                else {
//                    pFrame->pc+=3;
//                }
//                pFrame->sp--;
//                break;
//            case op_ifle:// 158 /*(0x9e)*/
//                if(pFrame->stack[pFrame->sp] <= 0) {
//                    pFrame->pc+= geti2(&code_iterator[pFrame->pc+1]);
//                }
//                else {
//                    pFrame->pc+=3;
//                }
//                pFrame->sp--;
//                break;
//                //Comparison instructions
//                
//                //Unconditional branch instructions
//            case op_goto: // 167 /*(0xa7)*/
//                pFrame->pc += geti2(&code_iterator[pFrame->pc+1]);
//                break;
//                //Table jumping instructions
//                
//                ////////////// Exceptions ///////////////////////
//            case op_athrow:
//                error = 1;
//                break;
//                
//                //////////////////////// Method Invocation and Return ////////
//                
//                //Method invocation instructions
            case op_invokespecial:
                i = getu2(&code_iterator[pFrame->pc+1]);
                class_index = pFrame->pClass->constant_pool[i - 1].info.CONSTANT_FieldMethodIMethod_info.class_index;
                nameAndType_index = pFrame->pClass->constant_pool[i - 1].info.CONSTANT_FieldMethodIMethod_info.name_and_type_index;
                
                class_name_index = pFrame->pClass->constant_pool[class_index - 1].info.CONSTANT_Class_info.name_index;
                
                class_name = GetStringFromConstPool(class_name_index, pFrame->pClass->constant_pool);
                
                pClass = fetchClass(pClassHeap, class_name, dmSize_ptr->clsHeap_size);
                
                //method_info *method;
                
                method->name_index = pFrame->pClass->constant_pool[nameAndType_index - 1].info.CONSTANT_NameAndType_info.name_index;
                
                method->descriptor_index = pFrame->pClass->constant_pool[nameAndType_index - 1].info.CONSTANT_NameAndType_info.descriptor_index;
                
                strName = GetStringFromConstPool(method->name_index, pFrame->pClass->constant_pool);
                strDesc = GetStringFromConstPool(method->descriptor_index, pFrame->pClass->constant_pool);
                
                if (strcmp(strName,"println") == 0) {
                    fv = pFrame->stack[pFrame->sp];
                    if (strcmp(fv->descriptor,"Ljava/lang/String;") == 0) {
                        printf("%s\n",fv->info.UTF8.bytes);
                        pFrame->sp--;
                    }
                    else {
                        if (strcmp(fv->descriptor,"I") == 0 || strcmp(fv->descriptor,"F") == 0) {
                            printf("%d\n",fv->info.I4.value);
                            pFrame->sp--;
                        }
                        else {
                            if (strcmp(fv->descriptor,"D") == 0 || strcmp(fv->descriptor,"J") == 0) {
                                printf("high = %d\n",fv->info.U8.high);
                                printf("low = %d\n",fv->info.U8.low);
                                pFrame->sp--;
                            }
                            
                        }
                        
                    }
                }
                else {
                    nIndex = seekMethodInClass(pClass, strName, strDesc);
                    
                    callMethod(pClass, stackFrame_ptr, dmSize_ptr, pClassHeap, strName, strDesc);
                }
                pFrame->pc += 3;
                break;


              case op_invokevirtual: //182
                i = getu2(&code_iterator[pFrame->pc+1]);
                class_index = pFrame->pClass->constant_pool[i - 1].info.CONSTANT_FieldMethodIMethod_info.class_index;
                nameAndType_index = pFrame->pClass->constant_pool[i - 1].info.CONSTANT_FieldMethodIMethod_info.name_and_type_index;
                
                class_name_index = pFrame->pClass->constant_pool[class_index - 1].info.CONSTANT_Class_info.name_index;
                
                class_name = GetStringFromConstPool(class_name_index, pFrame->pClass->constant_pool);
                
                pClass = fetchClass(pClassHeap, class_name, dmSize_ptr->clsHeap_size);
                
                //method_info *method;
                
                method->name_index = pFrame->pClass->constant_pool[nameAndType_index - 1].info.CONSTANT_NameAndType_info.name_index;
                
                method->descriptor_index = pFrame->pClass->constant_pool[nameAndType_index - 1].info.CONSTANT_NameAndType_info.descriptor_index;
                
                strName = GetStringFromConstPool(method->name_index, pFrame->pClass->constant_pool);
                strDesc = GetStringFromConstPool(method->descriptor_index, pFrame->pClass->constant_pool);
                
                if (strcmp(strName,"println") == 0) {
                    fv = pFrame->stack[pFrame->sp];
                    if (strcmp(fv->descriptor,"Ljava/lang/String;") == 0) {
                        printf("%s\n",fv->info.UTF8.bytes);
                        pFrame->sp--;
                    }
                    else {
                        if (strcmp(fv->descriptor,"I") == 0 || strcmp(fv->descriptor,"F") == 0) {
                            printf("%d\n",fv->info.I4.value);
                            pFrame->sp--;
                        }
                        else {
                            if (strcmp(fv->descriptor,"D") == 0 || strcmp(fv->descriptor,"J") == 0) {
                                printf("high = %d\n",fv->info.U8.high);
                                printf("low = %d\n",fv->info.U8.low);
                                pFrame->sp--;
                            }
                            
                        }
                        
                    }
                }
                else {
                    nIndex = seekMethodInClass(pClass, strName, strDesc);
                    
                    callMethod(pClass, stackFrame_ptr, dmSize_ptr, pClassHeap, strName, strDesc);
                }
                pFrame->pc += 3;
                break;
                
//            case op_invokestatic:// 184
//                //ExecuteInvokeVirtual(pFrame, invokestatic);
//                pFrame->pc+=3;
//                break;
//                //Method return instructions
//            case op_ireturn: //172 (0xac)
//                pFrame->stack[0]=pFrame->stack[pFrame->sp];			
//                return ireturn;
//                break;
                
            case op_return: //177 (0xb1): Return (void) from method
                printf("return\n");
                pFrame->sp = -1;
                pFrame->pc = 0;
                return 0;//METHOD_RETURN;
                
                break;
                //////////////// Thread Synchronization ////////////////////
                
            case op_monitorenter:// Enter and acquire object monitor
            case op_monitorexit:// Release and exit object monitor
                error = 1;
                break;
                
            default:
                error=1;
                break;
            
        }
        
    }
    
    
}


void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_aconst_null (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
void op_nop (Frame *stackFrame_ptr, ClassFile *pClassHeap, Object *pObjectHeap, dataMSize_t *dmSize_ptr ) {
    
}
#define op_aconst_null 1
#define op_iconst_m1  2
#define op_iconst_0  3
#define op_iconst_1  4
#define op_iconst_2  5
#define op_iconst_3  6
#define op_iconst_4  7
#define op_iconst_5  8
#define op_lconst_0  9
#define op_lconst_1  10
#define op_fconst_0  11
#define op_fconst_1  12
#define op_fconst_2  13
#define op_dconst_0  14
#define op_dconst_1  15
#define op_bipush  16
#define op_sipush  17
#define op_ldc  18
#define op_ldc_w  19
#define op_ldc2_w  20
#define op_iload  21
#define op_lload  22
#define op_fload  23
#define op_dload  24
#define op_aload  25
#define op_iload_0  26
#define op_iload_1  27
#define op_iload_2  28
#define op_iload_3  29
#define op_lload_0  30
#define op_lload_1  31
#define op_lload_2  32
#define op_lload_3  33
#define op_fload_0  34
#define op_fload_1  35
#define op_fload_2  36
#define op_fload_3  37
#define op_dload_0  38
#define op_dload_1  39
#define op_dload_2  40
#define op_dload_3  41
#define op_aload_0  42
#define op_aload_1  43
#define op_aload_2  44
#define op_aload_3  45
#define op_iaload  46
#define op_laload  47
#define op_faload  48
#define op_daload  49
#define op_aaload  50
#define op_baload  51
#define op_caload  52
#define op_saload  53
#define op_istore  54
#define op_lstore  55
#define op_fstore  56
#define op_dstore  57
#define op_astore  58
#define op_istore_0  59
#define op_istore_1  60
#define op_istore_2  61
#define op_istore_3  62
#define op_lstore_0  63
#define op_lstore_1  64
#define op_lstore_2  65
#define op_lstore_3  66
#define op_fstore_0  67
#define op_fstore_1  68
#define op_fstore_2  69
#define op_fstore_3  70
#define op_dstore_0  71
#define op_dstore_1  72
#define op_dstore_2  73
#define op_dstore_3  74
#define op_astore_0  75
#define op_astore_1  76
#define op_astore_2  77
#define op_astore_3  78
#define op_iastore  79
#define op_lastore  80
#define op_fastore  81
#define op_dastore  82
#define op_aastore  83
#define op_bastore  84
#define op_castore  85
#define op_sastore  86
#define op_pop  87
#define op_pop2  88
#define op_dup  89
#define op_dup_x1  90
#define op_dup_x2  91
#define op_dup2  92
#define op_dup2_x1  93
#define op_dup2_x2  94
#define op_swap  95
#define op_iadd  96
#define op_ladd  97
#define op_fadd  98
#define op_dadd  99
#define op_isub  100
#define op_lsub  101
#define op_fsub  102
#define op_dsub  103
#define op_imul  104
#define op_lmul  105
#define op_fmul  106
#define op_dmul  107
#define op_idiv  108
#define op_ldiv  109
#define op_fdiv  110
#define op_ddiv  111
#define op_irem  112
#define op_lrem  113
#define op_frem  114
#define op_drem  115
#define op_ineg  116
#define op_lneg  117
#define op_fneg  118
#define op_dneg  119
#define op_ishl  120
#define op_lshl  121
#define op_ishr  122
#define op_lshr  123
#define op_iushr  124
#define op_lushr  125
#define op_iand  126
#define op_land  127
#define op_ior  128
#define op_lor  129
#define op_ixor  130
#define op_lxor  131
#define op_iinc  132
#define op_i2l  133
#define op_i2f  134
#define op_i2d  135
#define op_l2i  136
#define op_l2f  137
#define op_l2d  138
#define op_f2i  139
#define op_f2l  140
#define op_f2d  141
#define op_d2i  142
#define op_d2l  143
#define op_d2f  144
#define op_i2b  145
#define op_i2c  146
#define op_i2s  147
#define op_lcmp  148
#define op_fcmpl  149
#define op_fcmpg  150
#define op_dcmpl  151
#define op_dcmpg  152
#define op_ifeq  153
#define op_ifne  154
#define op_iflt  155
#define op_ifge  156
#define op_ifgt  157
#define op_ifle  158
#define op_if_icmpeq  159
#define op_if_icmpne  160
#define op_if_icmplt  161
#define op_if_icmpge  162
#define op_if_icmpgt  163
#define op_if_icmple  164
#define op_if_acmpeq  165
#define op_if_acmpne  166
#define op_goto  167
#define op_jsr  168
#define op_ret  169
#define op_tableswitch  170
#define op_lookupswitch  171
#define op_ireturn  172
#define op_lreturn  173
#define op_freturn  174
#define op_dreturn  175
#define op_areturn  176
#define op_return  177
#define op_getstatic  178
#define op_putstatic  179
#define op_getfield  180
#define op_putfield  181
#define op_invokevirtual  182
#define op_invokespecial  183
#define op_invokestatic  184
#define op_invokeinterface  185
#define op_new  187
#define op_newarray  188
#define op_anewarray  189
#define op_arraylength  190
#define op_athrow  191
#define op_checkcast  192
#define op_instanceof  193
#define op_monitorenter  194
#define op_monitorexit  195
#define op_wide  196
#define op_multianewarray  197
#define op_ifnull  198
#define op_ifnonnull  199
#define op_goto_w  200
#define op_jsr_w  201
#define op_breakpoint  202


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
