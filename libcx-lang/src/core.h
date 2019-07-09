#ifndef _CX_CORE_H_
#define _CX_CORE_H_

#include "support.h"


#ifdef __cplusplus
extern "C" {
#endif 


void CxLog(const char*, ...);
void CxWarn(const char* , ...);
void CxError(const char*, ...);

void CxLogPush(const char*);
void CxLogPop();

void CxStr_Init(const char* );

unsigned int CxStr_Len(const char* );
unsigned int CxStr_Equals(const char*, const char*, CxBool ignoreCase );
unsigned int CxStr_Copy(const char*, const char* );
unsigned int CxStr_CopySize(const char*, const char*, unsigned size);
unsigned int CxStr_IndexOf(const char* , const char*);
unsigned int CxStr_LastIndexOf(const char* , const char*);

CxObj    CxStr_Split(const char*, const char*);

CxObj    CxString(const char* );
CxObj    CxInt(int v);
CxObj    CxFloat(float f);
CxObj    CxDouble(double );


#ifdef __cplusplus
} 
#endif 

#endif