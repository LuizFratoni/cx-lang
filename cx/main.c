

#include <stdio.h>
#include <string.h>



typedef void* CxObj;

typedef struct CxField_T {
    char *name;
    CxObj Type;
    unsigned int addr;
} * CxField;

typedef struct CxProperty_T {

} *CxProperty;

typedef struct CxMethod_T {
    char *clsName;
    unsigned int type;
    struct CxMethod_T* prev;
} *CxMethod;

typedef struct CxClass_T {

    char *clsName;
    CxObj clsParent;
    CxObj bundle;
    void* interfaces;
    struct CxClass_T* prev;
    struct CxMethod_T* lastMethod;
} *CxClass;

typedef struct CxBundle_T {
    void *interf;
    unsigned int refs;
    char *name;
    char *desc;
    char *version;
    struct CxClass_T* lastClass;
} *CxBundle;



CxObj CxNew_Bundle(const char* name, const char* desc, const char* version){
    printf("(CxBundle) Criando Bundle %s\n", name);
    CxBundle bundle = calloc( sizeof(struct CxBundle_T), 1);
    bundle->name = (char* ) malloc(strlen(name));
    bundle->desc = (char* ) malloc(strlen(desc));
    bundle->version = (char* ) malloc(strlen(version));
    bundle->refs = 1;
    strcpy(bundle->name, name);
    strcpy(bundle->desc, desc);
    strcpy(bundle->version, version);
    return bundle;
}


int main(int argc, char** argv){

    CxObj bundle = CxNew_Bundle("mymodule", "MOdule de Teste", "1.0");

    
    
    CxBundle_CreateClass(bundle, "Alpha");
}