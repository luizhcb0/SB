//
//  main.c
//  
//
//  Created by Luiz Henrique Campos Barboza on 09/12/15.
//
//
#include "macros.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <inttypes.h>
#include "LoadClass_ui.h"

char *opcodes_str_names[] = { "nop", "aconst_null", "iconst_m1", "iconst_0", "iconst_1", 
	"iconst_2", "iconst_3", "iconst_4", "iconst_5", "lconst_0", 
	"lconst_1", "fconst_0", "fconst_1", "fconst_2", "dconst_0", 
	"dconst_1", "bipush", "sipush", "ldc", "ldc_w", 
	"ldc2_w", "iload", "lload", "fload", "dload", 
	"aload", "iload_0", "iload_1", "iload_2", "iload_3", 
	"lload_0", "lload_1", "lload_2", "lload_3", "fload_0", 
	"fload_1", "fload_2", "fload_3", "dload_0", "dload_1", 
	"dload_2", "dload_3", "aload_0", "aload_1", "aload_2", 
	"aload_3", "iaload", "laload", "faload", "daload", 
	"aaload", "baload", "caload", "saload", "istore", 
	"lstore", "fstore", "dstore", "astore", "istore_0", 
	"istore_1", "istore_2", "istore_3", "lstore_0", "lstore_1", 
	"lstore_2", "lstore_3", "fstore_0", "fstore_1", "fstore_2", 
	"fstore_3", "dstore_0", "dstore_1", "dstore_2", "dstore_3", 
	"astore_0", "astore_1", "astore_2", "astore_3", "iastore", 
	"lastore", "fastore", "dastore", "aastore", "bastore", 
	"castore", "sastore", "pop", "pop2", "dup", 
	"dup_x1", "dup_x2", "dup2", "dup2_x1", "dup2_x2", 
	"swap", "iadd", "ladd", "fadd", "dadd", 
	"isub", "lsub", "fsub", "dsub", "imul", 
	"lmul", "fmul", "dmul", "idiv", "ldiv", 
	"fdiv", "ddiv", "irem", "lrem", "frem", 
	"drem", "ineg", "lneg", "fneg", "dneg", 
	"ishl", "lshl", "ishr", "lshr", "iushr", 
	"lushr", "iand", "land", "ior", "lor", 
	"ixor", "lxor", "iinc", "i2l", "i2f", 
	"i2d", "l2i", "l2f", "l2d", "f2i", 
	"f2l", "f2d", "d2i", "d2l", "d2f", 
	"i2b", "i2c", "i2s", "lcmp", "fcmpl", 
	"fcmpg", "dcmpl", "dcmpg", "ifeq", "ifne", 
	"iflt", "ifge", "ifgt", "ifle", "if_icmpeq", 
	"if_icmpne", "if_icmplt", "if_icmpge", "if_icmpgt", "if_icmple", 
	"if_acmpeq", "if_acmpne", "goto", "jsr", "ret", 
	"tableswitch", "lookupswitch", "ireturn", "lreturn", "freturn", 
	"dreturn", "areturn", "return", "getstatic", "putstatic", 
	"getfield", "putfield", "invokevirtual", "invokespecial", "invokestatic", 
	"xyzNotUsedxyz", "invokeinterface", "new", "newarray", "anewarray", "arraylength", 
	"athrow", "checkcast", "instanceof", "monitorenter", "monitorexit", 
	"wide", "multianewarray", "ifnull", "ifnonnull", "goto_w", 
	"jsr_w", "breakpoint" };

void loadClass( FILE *classPathF_ptr, ClassFile* clsHeap, dataMSize_t *dmSize ); 
u2 seekMethodInClass(ClassFile *class_ptr, char *methName_str, char *methDescriptor_str);

int main(){
    ClassFile* classHeap_ptr = malloc( sizeof( ClassFile ) );
	dataMSize_t *dmsize;
	dmsize->clsHeap_size = 0;
	dmsize->objHeap_size = 0;
	dmsize->stkHeap_size = 0;

	FILE *classPathF_ptr = fopen("testeStatic.class", "rb");
	if( classPathF_ptr == NULL ){
		printf("\nErro ao abrir");
		exit(1);
	}

    loadClass( classPathF_ptr, classHeap_ptr, dmsize );

    printf("\nConteudo do .class");
    printf("\n--------------------------------");
    print_ClassFile(classHeap_ptr);
 	
	u2 method_idx;
	method_idx = seekMethodInClass(classHeap_ptr, "<clinit>", "()V"); 
   	if( method_idx == -1 ){
		printf("\nDeu pau");
	}
	else{
		//printf("\n%hu",  method_idx);	
	 	//printf("%d\n",classHeap_ptr->methods[method_idx].name_index);

	}   
       
    return 0;
}

/**
* @brief Busca no classFile por um métodos específico e retorna o indice para a tabela de métodos
*
* @param class_ptr ponteiro para um classFile
* @param methName_str nome do método que se deseja buscar
* @param methDescriptor_str descritor do método, ()V por exemplo
*
* @return retorna o índice na tabela de métodos do classFile
*/
u2 seekMethodInClass(ClassFile *class_ptr, char *methName_str, char *methDescriptor_str){
	char *methodN;
	char *methodD;
	//char *bytes;
	//u2 str_size;
	for(int i = 0; i < class_ptr->methods_count; i++){
		//str_size = class_ptr->constant_pool[class_ptr->methods[i].name_inex - 1].info.CONSTANT_Utf8_info.length;	
		//methodN = malloc( (str_size + 1)*sizeof(char) );
		//bytes = class_ptr->constant_pool[class_ptr->methods[i].name_index - 1].info.CONSTANT_Utf8_info_bytes;
		
			
		methodN = class_ptr->constant_pool[class_ptr->methods[i].name_index - 1].info.CONSTANT_Utf8_info.bytes;
		methodD = class_ptr->constant_pool[class_ptr->methods[i].descriptor_index - 1].info.CONSTANT_Utf8_info.bytes;
		if( !strcmp(methodN, methName_str) && !strcmp(methodD, methDescriptor_str) ){
			return i;
		}
		
		/*for(int j = 0; j < str_size; j++){
			methodN[j] = bytes[j]; 
		} 
		methodN[str_size
		*/
	}
	return SEEK_NOTFOUND;
}
