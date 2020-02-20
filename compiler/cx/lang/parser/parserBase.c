

#include <parser.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define IS_ALPHA(parser) (parser->curCh >= 65 && parser->curCh <= 90) || (parser->curCh >= 97 && parser->curCh <= 122) 
#define IS_ALPHA_NUMERIC(parser) (parser->curCh >= 65 && parser->curCh <= 90) || (parser->curCh >= 97 && parser->curCh <= 122) || (parser->curCh >= 48 && parser->curCh <= 57)


////////////////////////////////////////

char CxTk_GetCh(CxParser parser){
    return parser->curCh;   
}

CxBool CxTk_Next(CxParser parser){
    if (parser->curCh == 10){
        parser->line++;
        parser->col = 0;
    }
    if (parser->cur < parser->end){
        parser->cur++;
        parser->curCh = *parser->cur;
        return CxTrue;
    } else return CxFalse;
}

CxBool CxTk_NextLine(CxParser parser){
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


CxBool CxTk_EscapeBlanks(CxParser parser){
    printf("Escape Blanks\n");

    while ( parser->cur < parser->end ) {
        printf("-");

        parser->col++;
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

CxBool CxTk_WaitNextLine(CxParser parser, CxBool *lineEnd){
    printf("Escape Blanks\n");

    *lineEnd = CxFalse;
    while ( parser->cur < parser->end ) {

        parser->col++;
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

CxBool CxTk_ReadName(CxParser parser, CxName *result){
    
    char *begin = parser->cur;


    while (parser->cur < parser->end){
        parser->col++;
        if ( IS_ALPHA_NUMERIC(parser) ){
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
    if (CxTk_EscapeBlanks(parser)){
        if ( CxTk_ReadName(parser, &lastName) ){
            while ( CxTk_WaitNextLine(parser, &lineEnd)){
                if (lineEnd) {
                    lastName->next = parser->imports;
                    parser->imports = lastName;
                    return CxTrue;
                }
                if (parser->curCh == ',' ){
                    parser->cur++; parser->curCh = *parser->cur;
                    if (CxTk_EscapeBlanks(parser)){
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




CxBool CxParse_Source(CxSource source, CxParser *result){

    CxParser parser = (CxParser) calloc(1, sizeof( struct CxParser_T ));
    parser->size = source->size;
    parser->data = source->data;
    parser->src  = source;

    parser->cur = parser->data;

    parser->end = parser->data+parser->size;
    parser->curCh = *parser->cur;

    if (result != NULL) *result = parser;

    printf("Parsing...\n");

    CxName lastName;
    CxBool lineEnd = CxFalse;

    CxBool body = CxFalse;

    while (CxTk_EscapeBlanks(parser)){
        printf("Caractere atual: %c", parser->curCh);
        if (IS_ALPHA(parser)){
            if (CxTk_ReadName(parser, &lastName)){
        
                if (strcmp(lastName->name, "import") == 0){
                    CxParser_ReadImports(parser);
                    body = CxTrue;
                    //break;
                } else {
                    printf("Identificador nao existe '%s'.\n", lastName->name);
                    //CxParser_Error(parser, 'Unknow Identifier', ' ');
                    if (!CxTk_NextLine(parser)) break;
                }
                printf("LIDO\n");
                printf("Palavra encontrada: \"%s\"\n", lastName->name);
            } 
        } else {
            CxParser_Error(parser,"Specting an identifier but '%c' found.", parser->curCh);
            if (!CxTk_NextLine(parser)) break;
        }

 
    }

    printf("*** TO AQUI: '%s'\n", parser->imports->name);
    if (parser->imports != NULL){
        printf("TEM IMPORTACAO");
    }

    return CxTrue;
    
}




