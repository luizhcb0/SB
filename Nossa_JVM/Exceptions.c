#include "macros.h"
//#include <unistd.h>
#include <stdio.h>

void error(int errorCode){
    switch( errorCode ){
        case NOTACLASS_ERR:
            printf("\n------------------------");
            printf("\nErro:");
            printf("\nO arquivo lido não foi reconhecido como um como um .class adequado");
            printf("\nSaindo...");
            printf("\n");
            //sleep(2);
            exit(1);
        case INCORRECTVERSION_ERR:
            printf("\n------------------------");
            printf("\nErro:");
            printf("\nVersão maior que 1.2.");
            printf("\nSaindo...");
            printf("\n");
            //sleep(2);
            exit(1);
        case NOTACLASS_ERR 2                               :
        case INCORRECTVERSION_ERR 1:
        case E_SUCCESS  0:
        case E_INVALID_NUM_ARGS  -1:
        case E_ARGV1_FILE_NOT_EXISTENT  -2 :
        case E_CAFEBABE  -3:
        case E_VERSION  -4:
        case W_NAOLIDOINTEIRO  -5 :
        case E_OPCAO_NAO_EXISTENTE  -6:
        case E_DOLAR_NOT_SUPPORTED  -7 :
        case E_EMPTY_FRAME_STACK  -8:
        case E_STACK_OVERFLOW  -9:
        case E_NO_MAIN_FOUND  -10:
        case E_EMPTY_STACK  -11:
        case E_NOTSUPPORTED_VERSION  -12:
        case E_NOTVALID_CP_INDEX  -13:
        case E_NEG_ARR_SIZE  -14:
        case E_NULL_POINTER  -15:
        case E_ARR_NOT_FOUND  -16 :
        case E_NOT_VALID_MARRAY_INFO  -17            :
        case E_NOT_SUPPORTED_ARRAY_TYPE  -18         :
        case E_DISTINCT_MARRAY_DIMENSIONS  -19       :
        case E_NOT_SUPPORTED_INSTRUCTION  -20        :
        case E_BAD_INPUT  -21                        :
        case E_NEGATIVE_ARRAY_SIZE  -22              :
        default:
            printf("\n------------------------");              
            printf("\nErro:");                                 
            printf("\nUm erro indefinido ocorreu");    }
            printf("\nSaindo...");                 } 
            printf("\n");
            //sleep(2);
            exit(1);
