#ifndef _CX_AOT_H
#define _CX_AOT_H

#include "../support.h"

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
    CxName type, name;
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
    CxName *implements;
    CxAnnotation annotations;
} *CxClass;

typedef struct CxSource_T {
    uint type;
    CxObj next;
    char *name;
    char *fileName;
    CxParser parser;
    CxClass  classes;
    CxMethod methods;
} *CxSourceUnit;

typedef struct CxBundle_T {
    uint type;
    CxObj next;
    char *name;
    char *desc;
    char *version;
    struct CxClass_T* lastClass;
    CxSourceUnit unities;
} *CxBundle;



#endif

