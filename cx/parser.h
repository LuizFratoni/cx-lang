#ifndef _CX_PARSER_H
#define _CX_PARSER_H

#include "aot.h"


typedef struct CxField_T {
    uint type;
    CxObj next;
    char *name;
    char *typeName;
    unsigned int addr;
} * CxField;

typedef struct CxProperty_T {

} *CxProperty;

typedef struct CxParam_T {
    uint type;
    CxObj next;
    char *name;
    char *typeName;
} *CxParam;

typedef struct CxMethod_T {
    uint type;
    CxObj next;
    char *clsName;
    char *typeName;
} *CxMethod;

typedef struct CxClass_T {
    char *name;

} *CxClass;


typedef struct CxLog_T {
    char type;
    unsigned int col, line;
    char *text;
    CxObj next;
} * CxLog;

typedef struct CxParser_T {

    char *name;
    char *data;
    unsigned int line, col;
    unsigned int size;
    char *cur;
    char *end;
    char curCh;
    unsigned int errors, warns;

    CxObj nextFile;
    CxBool success;
    CxName imports;

} *CxParser;


CxBool CxTk_ReadName(CxParser, CxName* name);
CxBool CxTk_ReadValue(CxParser);
CxBool CxTk_EscapeBlanks(CxParser);
CxBool CxTk_WaitLineEnd(CxParser, *CxBool);
CxBool CxTk_NextLine(CxParser);

CxParser CxParser_CreateFromString(const char*);
CxParser CxParser_CreateFromFile(const char*);

CxParser CxParser_ParseSource(CxParser); //ParseUnit, ParseFile
CxParser CxParser_ParseStatement(CxParser, Statement *);


#endif

