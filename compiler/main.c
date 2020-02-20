

#include <stdio.h>
#include <string.h>

#include "cx/lang/aot.h"

#include "cx/lang/parser.h"


void logfunc(void* instance, int row, int col, char *msg){
    printf("Error At line: %d, col: %d - %s", msg);
}

int parseFile(char* filename){

    CxBundle bnd = CxCreate_Bundle("Temp", "Temp", "");
    CxSource src = CxCreate_SourceFromFile(filename);

    CxParser parser;
    CxParse_Source(src, &parser);
}

int main(int argc, char** argv){

    
    if (argc < 3){
        printf("cx-error: Invalid Command Line\n");
        return -1;
    }

    if (strcmp(argv[1], "parser")){
        return parseFile(argv[2]);
    } else {
        printf("cx-error : Unknown Command\n";
        return -1;
    }

}