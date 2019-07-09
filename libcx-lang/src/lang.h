
#ifndef _CX_LANG_H
#define _CX_LANG_H

#include "support.h"


typedef struct ICxBundle_T {
    CxBaseMethods
    CxObj (*createClass)(CxObj, const char* name);
} *ICxBundle;

#ifdef __cplusplus
extern "C" {
#endif 

#define CxBundle_CreateClass(bundle, name)  ((ICxBundle) ((struct CxObj_T*) bundle)->interf)->createClass(bundle, name)

CxObj CxObjects_NewBundle(const char* name);

#ifdef __cplusplus
}
#endif 


#endif
