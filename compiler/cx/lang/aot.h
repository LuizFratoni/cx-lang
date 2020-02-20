#ifndef _CX_AOT_H
#define _CX_AOT_H

#include "../support.h"

#define CX_AOT_ELEMENT_NONE         0


#define CX_AOT_EXPRESSION           1
#define CX_AOT_IDENTIFIER           2    
#define CX_EXP_CONSTANT             3
#define CX_EXP_ASSIGN
#define CX_EXP_DECLARATION
#define CX_EXP_METHOD_INVOKE
#define CX_EXP_OBJECT_MEMBER
#define CX_EXP_MATH_OPERATION       
#define CX_EXP_COND_OPERATION      
#define CX_EXP_ARRAY_ITEM 

#define CX_EXP_BULK_GET
#define CX_EXP_BULK_SET
#define CX_EXP_FIELD_SELECTION  

#define CX_EXP_IF
#define CX_EXP_FOR
#define CX_EXP_WHILE
#define CX_EXP_FOREACH


#define CX_EXP_MATH_OPERATION_SUM
#define CX_EXP_MATH_OPERATION_MINUS
#define CX_EXP_MATH_OPERATION_MULT
#define CX_EXP_MATH_OPERATION_DIV
#define CX_EXP_MATH_OPERATION_REM
#define CX_EXP_MATH_OPERATION_POWER

#define CX_EXP_COND_OPERATION_EQUAL
#define CX_EXP_COND_OPERATION_LESSOREQUAL
#define CX_EXP_COND_OPERATION_BIGGEROREQUAL
#define CX_EXP_COND_OPERATION_LESSER
#define CX_EXP_COND_OPERATION_BIGGER
#define CX_EXP_COND_OPERATION_REGEX
#define CX_EXP_COND_OPERATION_NOT

#define CX_AOT_BUNDLE_ELEMENT       2
#define CX_AOT_ELEMENT_CLASS        3
#define CX_AOT_ELEMENT_FIELD        4
#define CX_AOT_ELEMENT_METHOD       5
#define CX_AOT_ELEMENT_PROPERTY     6
#define CX_AOT_ELEMENT_ANNOTATION   7

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
} * CxExpression;

typedef struct CxAssignExp_T{
    uint type;
    void *next;
    CxExpression left;
    CxExpression right;
} *CxAssignExp;

typedef struct CxConstantExp_T {
    uint type;
    void *next;
    unsigned char valueType;
} *CxConstantExp;

typedef struct CxDeclareExp_T {
    uint type;
    void *next;
    CxName typeName, name;
} *CxDeclareExp;


typedef struct CxStatement_T {
    uint type;
    void *next;
} *CxStatement;

typedef struct CxInvokeExp_T {
    uint type;
    void *next;
    CxExpression parent;
    CxExpression params;

} *CxInvokeExp;

typedef struct CxUnaryOperation_T {
    uint type;
    void *next;
    uint op;
    CxExpression left;
} *CxUnaryOperation;

typedef struct CxBinaryOperation_T {
    uint type;
    void *next;
    uint op;
    CxExpression left;
    CxExpression right;
} *CxBinaryOperation;


//// CLASS DEFINITION

typedef struct CxAnnotation_T {
    uint type;
    CxObj next; 
    char  name;
} *CxAnnotation;

typedef struct CxField_T {
    uint type;
    CxObj next;
    char *name;
    char *typeName;
    unsigned int addr;
    CxAnnotation annotations;
} * CxField;

typedef struct CxProperty_T {

} *CxProperty;

typedef struct CxParam_T {
    uint type;
    CxObj next;
    char *name;
    char *typeName;
    CxAnnotation annotations;
} *CxParam;

typedef struct CxMethod_T {
    uint type;
    CxObj next;
    char *clsName;
    char *typeName;
    uint methodType;
    CxParam params;
    CxStatement statements;
    CxAnnotation annotations;
    uint callConvention;
    void *compiled;
} *CxMethod;

typedef struct CxClass_T {
    uint type;
    CxObj next;
    char *name;
    char *extends;
    CxName implements;
    CxAnnotation annotations;
} *CxClass;

typedef struct CxSource_T {
    uint type;
    CxObj next;
    char *name;
    char *fileName;
    char *data;
    uint size;
    CxName   imports;
    CxClass  classes;
    CxMethod methods;
} *CxSource;

typedef struct CxBundle_T {
    uint type;
    CxObj next;
    char *name;
    char *desc;
    char *version;
    struct CxClass_T* lastClass;
} *CxBundle;




//////

/*
CxBundle CxCreate_Bundle(const char* name, const char* desc, const char* version);
CxSource CxCreate_SourceFromString(CxScope bnd, const char *name, const char *src);
CxSource CxCreate_SourceFromFile(CxScope bnd, const char* filename);
CxSource CxCreate_SourceFromBuffer(CxScope bnd, const char *name, uint size, void* buffer);
*/

#endif

