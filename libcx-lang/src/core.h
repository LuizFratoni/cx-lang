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

void Cx


#ifdef __cplusplus
} 
#endif 

#endif