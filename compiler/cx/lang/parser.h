#ifndef _CX_PARSER_H
#define _CX_PARSER_H

#include "aot.h"


typedef struct CxLog_T {
    char type;
    unsigned int col, line;
    char *text;
    CxObj next;
} * CxLog;

typedef struct CxParser_T {

    uint type;
    CxObj next;
    char *name;

    CxClass  classes;
    CxMethod methods;

    unsigned int errors, warns;

    CxBool success;
    CxName imports;

    //parsing aux
    char *data;
    unsigned int line, col;
    unsigned int size;
    char *cur;
    char *end;
    char curCh;

} *CxParser;


/*
CxBool CxTk_ReadName(CxParser, CxName* name);
CxBool CxTk_ReadValue(CxParser);
CxBool CxTk_EscapeBlanks(CxParser);
CxBool CxTk_WaitLineEnd(CxParser, *CxBool);
CxBool CxTk_NextLine(CxParser);*/


CxBool CxParse_Source(CxSource, CxParser *result);
CxBool CxParse_Statement(CxParser, CxStatement *result);

#endif

