#ifndef _CX_AOT_H
#define _CX_AOT_H

#include "types.h"

typedef struct CxAOTNode_T {
    uint type;
    void *next;
} *CxAOTNode, *CxElement;

typedef struct CxName_T { 
    uint type;
    void *next;
    char *name;
    int size;
} *CxName;


//// EXPRESSIONS 


typedef struct CxExpression_T {
    uint type;
    void *next;
} *CxExpresion;

typedef struct CxAssignExp_T{
    uint type;
    void *next;
    CxEpression left;
    CxEpression right;
} *CxAssignExp;

typedef struct CxConstantExp_T {
    uint type;
    void *next;
    unsigned char valueType;
} *CxConstantExp;

typedef struct CxDeclareExp_T {
    uint type;
    void *next;
    CxName type, name;
} *CxDeclareExp;


typedef struct CxStatement_T {
    uint type;
    void *next;
} *CxStatement;

typedef struct CxInvokeExp_T {
    uint type;
    void *next;
    CxExpresion parent;
    CxEpression params;

} *CxInvokeExp;



#endif