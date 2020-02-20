

#include <parser.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




#define IS_ALPHA(parser) (parser->curCh >= 65 && parser->curCh <= 90) || (parser->curCh >= 97 && parser->curCh <= 122) || (parser->curCh >= 48 && parser->curCh <= 57)

typedef struct CxName_T {
    char *name;
    int  size;
    CxObj next;
} *CxName;


typedef struct CxField_T {
    char *name;
    char *typeName;
    unsigned int addr;
    CxObj next;
} * CxField;

typedef struct CxProperty_T {

} *CxProperty;

typedef struct CxParam_T {
    char *name;
    char *typeName;
} *CxParam;

typedef struct CxMethod_T {
    char *clsName;
    char *typeName;
    CxObj next;
} *CxMethod;

typedef struct CxClass_T {
    char *name;

} *CxClass;


typedef struct CxLog_T {
    char type;
    unsigned int col, line;
    char *text;
    CxObj next;
} * CxLog;

typedef struct CxParser_T {

    char *name;
    char *data;
    unsigned int line, col;
    unsigned int size;
    char *cur;
    char *end;
    char curCh;
    unsigned int errors, warns;

    CxObj nextFile;
    CxBool success;
    CxName imports;

} *CxParser;


CxParser CxParser_CreateFromFile(const char* fileName){
    CxParser parser = (CxParser) calloc(1, sizeof( struct CxParser_T ));
    FILE * file = fopen(fileName, "r");
    
    fseek(file, 0, SEEK_END );
    parser->size = ftell(file);
    fseek(file, 0, SEEK_SET);

    parser->data = (void*) malloc(( parser->size));
    
    fread ( parser->data, parser->size, 1, file );
    parser->cur = parser->data;

    parser->end = parser->data+parser->size;
    parser->curCh = *parser->cur;

    return parser;
}

CxParser CxParser_CreateFromString(const char* str){
    CxParser parser = (CxParser) calloc(1, sizeof( struct CxParser_T ));

    parser->size = strlen(str);
    parser->data = malloc( parser->size + 1);
    strcpy(parser->data, str);
    parser->cur = parser->data;
    parser->end = parser->data+parser->size;
    parser->curCh = *parser->cur;

    return parser;
}



////////////////////////////////////////

CxBool nextLine(CxParser parser){
    while ( parser->cur < parser->end ) {
        if (parser->curCh == 10){
            parser->line++;
            parser->col = 0;
            parser->cur++; parser->curCh = *parser->cur;
            return CxTrue;
        } 

        parser->cur++;
        parser->curCh = *parser->cur;
    }
    return CxFalse;

}


CxBool escapeBlanks(CxParser parser){
    printf("Escape Blanks\n");

    while ( parser->cur < parser->end ) {
        printf("-");


        if (parser->curCh == 10){
            parser->line++;
            parser->col = 0;
        }
        else if (parser->curCh == ' ' || parser->curCh == 8 || parser->curCh == 13){

        } else {
            return CxTrue;
        }

        parser->cur++;
        parser->curCh = *parser->cur;
    }

    printf("**** TERMINOU VAZIO ****\n");

    return CxFalse;
}

CxBool escapeBlanksOrWaitEnd(CxParser parser, CxBool *lineEnd){
    printf("Escape Blanks\n");

    *lineEnd = CxFalse;
    while ( parser->cur < parser->end ) {
        printf("-");


        if (parser->curCh == 10){
            parser->line++;
            parser->col = 0;
            parser->cur++;
            parser->curCh = *parser->cur;
            *lineEnd = CxTrue;
            return CxTrue;
        }
        else if (parser->curCh == ' ' || parser->curCh == 8 || parser->curCh == 13){

        } else if (parser->curCh == ';'){
            parser->cur++;
            parser->curCh = *parser->cur;
            *lineEnd = CxTrue;
            return CxTrue;
        }
        else {
            return CxTrue;
        }

        parser->cur++;
        parser->curCh = *parser->cur;
    }

    return CxFalse;
}

CxBool readText(CxParser parser, CxName *result){
    
    char *begin = parser->cur;


    while (parser->cur < parser->end){
        if ( IS_ALPHA(parser) ){
            parser->cur++;
            parser->curCh = *parser->cur;
        } else {
            if (begin < parser->cur){
                CxName name = (CxName) malloc( sizeof(struct CxName_T));
                name->size = parser->cur - begin;
                name->name = (char*) malloc( name->size + 1);
                strncpy(name->name, begin, name->size );
                name->next = NULL;
                *result = name;
            } else { return CxFalse; } 

            return CxTrue;
        }
    }

    return CxFalse;
}




/////////////////////////////////////////

void CxParser_Error(CxParser parser, const char* msg, char ch){
    printf("\n***** ERROR:");
    printf(msg, ch);
    printf("\n");
}

CxBool CxParser_ReadImports(CxParser parser){

    CxName lastName;
    CxBool lineEnd = CxFalse;

    printf("- Reading import");
    if (escapeBlanks(parser)){
        if ( readText(parser, &lastName) ){
            while ( escapeBlanksOrWaitEnd(parser, &lineEnd)){
                if (lineEnd) {
                    lastName->next = parser->imports;
                    parser->imports = lastName;
                    return CxTrue;
                }
                if (parser->curCh == ',' ){
                    parser->cur++; parser->curCh = *parser->cur;
                    if (escapeBlanks(parser)){
                        if ( IS_ALPHA(parser) ){
                            readText(parser, &lastName);
                            lastName->next = parser->imports;
                            parser->imports = lastName;
                        } else {
                            CxParser_Error(parser, "Expecting a name but '%c' found.", parser->curCh);
                            return CxTrue;
                        }
                    } else {
                        return CxFalse;
                    }
                } else {
                    CxParser_Error(parser, "Expecting ',' but '%c' found.", parser->curCh);
                    return CxTrue;
                }
            }
        } else return CxFalse;
    } return CxFalse;

    return CxTrue;
}

CxBool CxParser_



CxBool CxParser_Begin(CxParser parser){
    printf("Parsing...\n");

    CxName lastName;
    CxBool lineEnd = CxFalse;

    CxBool body = CxFalse;

    while (escapeBlanks(parser)){
        printf("Caractere atual: %c", parser->curCh);
        if (IS_ALPHA(parser)){
            if (readText(parser, &lastName)){
        
                if (strcmp(lastName->name, "import") == 0){
                    CxParser_ReadImports(parser);
                    body = CxTrue;
                    //break;
                } else {
                    printf("Identificador nao existe '%s'.\n", lastName->name);
                    //CxParser_Error(parser, 'Unknow Identifier', ' ');
                    if (!nextLine(parser)) break;
                }
                printf("LIDO\n");
                printf("Palavra encontrada: \"%s\"\n", lastName->name);
            } 
        } else {
            CxParser_Error(parser,"Specting an identifier but '%c' found.", parser->curCh);
            if (!nextLine(parser)) break;
        }

 
    }

    printf("*** TO AQUI: '%s'\n", parser->imports->name);
    if (parser->imports != NULL){
        printf("TEM IMPORTACAO");
    }

    return CxTrue;
    
}





int main(int argc, char** argv){
    printf("Inicializando parser\n");

    CxParser parser = CxParser_CreateFromString("import teste, alpha; \n class MyClass { } ");

    CxParser_Begin(parser);

    printf("Finalizado\n");
    return 0;

}
