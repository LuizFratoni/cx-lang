
#include "aot.h"

#include <stdio.h>


CxBundle CxCreate_Bundle(const char* name,const char* version){
    printf("(CxBundle) Criando Bundle %s\n", name);
    CxBundle bundle = calloc( sizeof(struct CxBundle_T), 1);
    bundle->name = (char* ) malloc(strlen(name) + 1);
    bundle->version = (char* ) malloc(strlen(version) + 1);
    strcpy(bundle->name, name);
    strcpy(bundle->version, version);
    return bundle;
}

CxSource CxCreate_SourceFromString(CxBundle bnd, const char *name, const char *src){
    CxSource parser = (CxSource) calloc(1, sizeof( struct CxSource_T ));
    parser->name = malloc(strlen(name)+1);
    strcpy(parser->name, name);
    parser->size = strlen(src);
    printf("CxSource: Creating source with size: %u\n", parser->size);
    parser->data = malloc( parser->size + 1);
    strcpy(parser->data, src);

    return parser;
}

CxSource CxCreate_SourceFromFile(CxBundle bnd, const char* filename){
    CxSource parser = (CxSource) calloc(1, sizeof( struct CxSource_T ));
    FILE * file = fopen(filename, "r");
    
    parser->name = malloc(strlen(filename) + 1);
    strcpy(parser->name, filename);

    fseek(file, 0, SEEK_END );
    parser->size = ftell(file);
    fseek(file, 0, SEEK_SET);

    parser->data = (void*) malloc(( parser->size));
    
    fread ( parser->data, parser->size, 1, file );


    return parser;
}


CxSource CxCreate_SourceFromBuffer(CxBundle bnd, const char *name, uint size, void* buffer){
    CxSource parser = (CxSource) calloc(1, sizeof( struct CxSource_T ));
    parser->name = malloc(strlen(name)+1);
    strcpy(parser->name, name);
    parser->size = size;
    parser->data = buffer;

    return parser;
}
