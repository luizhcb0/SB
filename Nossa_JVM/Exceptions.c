#include "macros.h"
//#include <unistd.h>
#include <stdio.h>

void errMsgAndExit(int errorCode){
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
        default:
            printf("\n------------------------");
            printf("\nErro:");
            printf("\nUm erro indefinido ocorreu");
            printf("\nSaindo...");
            printf("\n");
            //sleep(2);
            exit(1);
    }
} 
