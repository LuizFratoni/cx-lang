
#include "aot.h"



CxObj CxCreate_Bundle(const char* name, const char* desc, const char* version){
    printf("(CxBundle) Criando Bundle %s\n", name);
    CxBundle bundle = calloc( sizeof(struct CxBundle_T), 1);
    bundle->name = (char* ) malloc(strlen(name));
    bundle->desc = (char* ) malloc(strlen(desc));
    bundle->version = (char* ) malloc(strlen(version));
    strcpy(bundle->name, name);
    strcpy(bundle->desc, desc);
    strcpy(bundle->version, version);
    return bundle;
}

CxObj CxCreate_SourceFromString(CxBundle bnd, const char *name, const char *src){

}

CxObj CxCreate_SourceFromFile(CxBundle bnd, const char *name, const char* filename){

}


CxObj CxCreate_SourceFromBuffer(CxBundle bnd, const char *name, uint size, void* buffer){

}
