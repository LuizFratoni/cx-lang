/**
 * EVOVIE SOFTWARE FOUNDATION
 * CX PLATAFORM - Support Interfaces and Specification
 * 
 * @name cx platform - support
 * @description Support Interfaces and Specification
 * @version 0.1
 * @author Luiz Fratoni - luizfratoni@gmail.com
*/


#ifndef _EVOVIE_CX_CORE_H_
#define _EVOVIE_CX_CORE_H_

#define CxNull                  0

typedef unsigned char           byte;
typedef unsigned short          uint16;
typedef signed   short          int16;
typedef unsigned int            uint;
typedef long     int            Long;

#define Char                    char
#define StringPtr               char*
#define UTF8Char                char
#define UTF8StringPtr           char*
typedef void *					ObjectRef;
typedef void*                   CxObj;
typedef unsigned long           CxDate;
typedef unsigned long           CxTime;
typedef const char*             CxCLSID;

typedef unsigned char           u8;
typedef unsigned short          u16;
typedef unsigned int            u32;
typedef unsigned long           u64;

typedef char                    i8;
typedef short                   i16;
typedef int                     i32;
typedef long                    i64;

#ifdef __cplusplus
typedef bool                    CxBool;
#else
typedef unsigned char           CxBool;
#endif


#define CXNULL 0
#define null 0
#define nil  0

typedef void  cx_method(CxObj);
typedef CxObj cx_cast(CxObj, CxCLSID, CxObj*);
typedef CxObj cx_allocator();
typedef CxObj cx_signal(CxObj, const char* signal, ...);

///Common methods
typedef CxObj  cx_method_return(CxObj);
typedef CxBool cx_method_return_bool(CxObj);


typedef struct CxBaseType_T {
    cx_method *addRef;
    cx_cast   *queryInterface;
    cx_method *release;
} *CxBaseType;

#define CxBaseMethods cx_method *addRef; cx_cast *queryInterface; cx_method *release; cx_signal *signal;

struct CxObj_T {
    CxBaseType interf;
};



#define CxObj_AddRef(obj) ( (struct CxObj_T *) obj)->interf->addRef(obj)
#define CxObj_Release(obj) ( (struct CxObj_T *) obj)->interf->release(obj)
#define CxCast(obj, clsid, robj) ( (struct CxObj_T *) obj)->interf->queryInterface(obj, clsid, robj) 

#define CxSignal(obj, ...) ( (struct CxObj_T *) obj)->interf->signal(obj, __VA_ARGS__)

/////////////////////////////////////////




CxObj CxLogger_Init();
typedef void CxLogWrite(CxObj log, const char *fmt, ... );

typedef struct ICxLog_T {
    CxBaseMethods
    CxLogWrite *info;
    CxLogWrite *debug;
    CxLogWrite *error;
} *ICxLog;

typedef CxObj  ICxRuntimeImport(const char* libname);
typedef CxBool ICxRuntimeImports(uint libs, const char* libname);
typedef CxBool ICxRuntimeAddPath(const char* );
typedef CxObj  ICxRuntimeGetObject(CxCLSID);

typedef struct CxRuntime_T {
    ICxRuntimeImport*  import;
    ICxRuntimeImports* imports;
    ICxRuntimeAddPath* addPath;
    ICxRuntimeGetObject* getObject;
} *CxRuntime;

typedef int CxEntryPoint(CxObj runtime, CxObj logger); // 

/////////////////////




#endif

