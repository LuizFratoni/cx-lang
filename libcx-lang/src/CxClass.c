#include "lang.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void* CxObj;

typedef struct CxField_T {
    void *interf;
    char *name;
    CxObj Type;
    unsigned int addr;
} * CxField;

typedef struct CxProperty_T {

} *CxProperty;

typedef struct CxMethod_T {
    void *intef;
    char *clsName;
    unsigned int type;
    struct CxMethod_T* prev;
} *CxMethod;

typedef struct CxClass_T {
    void *interf;
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
    struct CxClass_T* lastClass;
} *CxBundle;

void cx_bundle_addRef(CxObj obj){
    ((CxBundle) obj)->refs++;
}

void cx_bundle_release(CxObj obj){
    printf("(CxBundle) Free Bundle\n");
    if( ((CxBundle) obj)->refs-- <= 0)
        free(obj);
}

CxObj cx_bundle_createClass(CxObj obj, const char* name){
    printf("Vai criar classe\n");
    printf("Criando Classe em Bundle: %s\n", ((CxBundle) obj)->name);
    printf("\nUHUUULLLL esta criando classe %s\n\n", name);
}

const struct ICxBundle_T CxBundleClass = {
    cx_bundle_addRef, 
    0,
    cx_bundle_release,
    0, 
    &cx_bundle_createClass
};


CxObj CxObjects_NewBundle(const char* name){
    printf("(CxBundle) Criando Bundle %s\n", name);
    CxBundle bundle = calloc( sizeof(struct CxBundle_T), 1);
    bundle->name = (char* ) malloc(strlen(name));
    bundle->refs = 1;
    strcpy(bundle->name, name);
    bundle->interf = &CxBundleClass;

    return bundle;
}

#ifdef DEBUG

#include <stdio.h>

int myMethodFunc(CxObj obj, int a, int b){

}

int main(){
    printf("Tudo certo versao 2\n");

    CxObj bundle = CxObjects_NewBundle("Module Teste");
    
    CxBundle_CreateClass(bundle, "Alpha");
}


#endif

