#ifndef _CX_PARSER_H
#define _CX_PARSER_H

typedef void * CxObj;
typedef char CxBool;

#define CX_TRUE  1
#define CX_FALSE 0

#define CxTrue  0xff
#define CxFalse 0


typedef struct CxExpression_T {
    unsigned char type;
    void *next;
} *CxExpresion;

typedef struct CxAssignExp_T{
    unsigned char type;
    void *next;
    CxEpression left;
    CxEpression right;
} *CxAssignExp;

typedef struct CxConstantExp_T {
    unsigned char type;
    void *next;
    unsigned char valueType;
} *CxConstantExp;

typedef struct CxDeclareExp_T {
    unsigned char type;
    void *next;
    CxName type, name;
} *CxDeclareExp;

typedef struct CxName_T { 
    unsigned char type;
    void *next;
    char *name;
    int size;
} *CxName;


typedef struct CxInvokeExp_T {
    unsigned char type;
    void *next;
    CxExpresion parent;
    CxEpression params;

} *CxInvokeExp;




CxBool CxTk_ReadName(CxParser, CxName* name);
CxBool CxTk_ReadValue(CxParser);
CxBool CxTk_EscapeBlanks(CxParser);
CxBool CxTk_WaitLineEnd(CxParser, *CxBool);
CxBool CxTk_NextLine(CxParser);

CxParser 


#endif

