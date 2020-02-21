

#include "../parser.h"
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
    while ( parser->cur < parser->end ) {

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

    return CxFalse;
}

CxBool CxTk_WaitNextLine(CxParser parser, CxBool *lineEnd){

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
    
    if (*result != NULL){
        free((*result)->name);
        free(*result);
    }
    char *begin = parser->cur;


    while (parser->cur < parser->end){
        parser->col++;
        if ( IS_ALPHA_NUMERIC(parser) ){
            parser->cur++;
            parser->curCh = *parser->cur;
        } else {
            if (begin < parser->cur){
                CxName name = (CxName) malloc( sizeof(struct CxName_T));
                name->size = parser->cur - begin ;
                name->name = (char*) malloc( name->size + 1);
                strncpy(name->name, begin, name->size );
                name->name[name->size] = 0;
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

#define PARSE_STEP(x) if (!x) goto error

CxBool CxParse_Class(CxParser parser) {
    
    printf("CxParser: Parsing Class\n");
    CxName name = NULL;
    CxClass cls = (CxClass) calloc(1, sizeof(struct CxClass_T));
    cls->implements = NULL;
 
    const char* step = "Reading Class name";

    PARSE_STEP ( CxTk_EscapeBlanks(parser) );
    PARSE_STEP ( CxTk_ReadName(parser, &name) );
    
    printf("CxParser:: Class:: Name %s\n", name->name);

    step = "Reading Class Definition";
    PARSE_STEP ( CxTk_EscapeBlanks(parser));

    if (IS_ALPHA(parser)){
    PARSE_STEP ( CxTk_ReadName(parser, &name) );
    printf("Encontrou palavra '%s'\n", name->name);
    
    CxBool readBody = CxTrue;

    if (strcmp(name->name, "extends") == 0){
        step = "Reading Class Parent";
        PARSE_STEP( CxTk_EscapeBlanks(parser) );
        PARSE_STEP( CxTk_ReadName(parser, &name));
        printf("----> Class inherits from %s\n", name->name);
        cls->extends = name->name;
        free(name); name = NULL;

        PARSE_STEP( CxTk_EscapeBlanks(parser) );
        printf("CONTINUANDO '%c' %d\n", parser->curCh, IS_ALPHA(parser));
        if (IS_ALPHA(parser)){
            printf("Reading IMPLEMENTATIONS\n");
            readBody = CxFalse;
            PARSE_STEP(CxTk_ReadName(parser, &name));
        } else {
            printf("NOT ALPHA\n");
            if (parser->curCh == '{') {
                readBody = CxTrue;
                CxTk_Next(parser);
            }
            else goto error;
        } 
    }

    if (readBody == CxFalse){
        if (strcmp(name->name, "implements") == 0){
            printf("Reading implementations\n");
            step = "Reading class implementations";
            while( 1 ){
                PARSE_STEP( CxTk_EscapeBlanks(parser) );
                if (IS_ALPHA(parser)){
                    PARSE_STEP( CxTk_ReadName(parser, &name) );
                    printf("CxParser: Class implementing %s\n", name->name);
                     name->next = cls->implements;
                     cls->implements = name;
                     free(name); name = NULL;
                     readBody = CxTrue;
                } else {
                    if (readBody == CxTrue){
                        if (parser->curCh == ','){ 
                            CxTk_Next(parser);
                            readBody = CxFalse;
                        } else if (parser->curCh == '{'){
                            CxTk_Next(parser);
                            break;
                        }
                    } else goto error;
                }
            }

        } else {
            step = "Invalid identifier of a class";
            goto error;
        }
    }
    } else if (parser->curCh == '{'){
        CxTk_Next(parser);
    } else {
        goto error;
    }


    printf("CxParser:: READING CLASS BODY\n");

    step = "Reading Class Body";
    while(1){
        PARSE_STEP( CxTk_EscapeBlanks(parser));
        if (parser->curCh == '}'){
            printf("CxParser: Class Body Read\n");
            CxTk_Next(parser);
            break;
        } else if (parser->curCh == '@'){
            // TODO: Read ANNOTATION
        } else if ( IS_ALPHA(parser)){
            CxTk_Next(parser);
        } else {
            CxParser_Error(parser, "Specting a class member declaration ", ' ');
            CxTk_NextLine(parser);
        }
    }



    goto ok;

    error:
        printf("**ERRROR PARSING CLASS: %s\nCol: %d, Row: %d, curChar: %c\n", step, parser->col, parser->line, parser->curCh);
        CxTk_NextLine(parser);
        return CxFalse;

    ok:
        return CxTrue;

}


CxBool CxParser_ReadImports(CxParser parser){

    CxName lastName = NULL;
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
                            CxTk_ReadName(parser, &lastName);
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

#define PARSE_STEP(x) if (!x)  goto error;


CxBool CxParse_Source(CxSource source, CxParser *result){

    printf("CxParser: Stating parser of %ul...\n", source);
    CxParser parser = (CxParser) calloc(1, sizeof( struct CxParser_T ));

    parser->size = source->size;
    parser->data = source->data;
    //parser->src  = source;

    parser->cur = parser->data;

    parser->end = parser->data + parser->size;
    parser->curCh = *parser->cur;

    if (result != NULL) *result = parser;



    CxName lastName = NULL;
    CxBool lineEnd = CxFalse;

    CxBool body = CxFalse;

    printf("CxParser: Parsing Source\n");

    while (CxTk_EscapeBlanks(parser)){
        if (IS_ALPHA(parser)){
            if (CxTk_ReadName(parser, &lastName)){
        
                if (strcmp(lastName->name, "import") == 0){
                    if (body == CxFalse){
                        CxParser_ReadImports(parser);
                    } else {
                        CxParser_Error(parser,"Misplaced import directive. Must be on the header of the source.\n", ' ');
                        CxTk_NextLine(parser);
                    }
                    
                    //break;
                } if (strcmp(lastName->name, "class") == 0){
                    CxParse_Class(parser);
                }
                else {
                    printf("Identificador nao existe '%s'.\n", lastName->name);
                    //CxParser_Error(parser, 'Unknow Identifier', ' ');
                    if (!CxTk_NextLine(parser)) break;
                }
                printf("LIDO\n");
                printf("Palavra encontrada: \"%s\"\n", lastName->name);
            } 
        } else {
            CxParser_Error(parser,"Specting an identifier but '%c' found.\n", parser->curCh);
            if (!CxTk_NextLine(parser)) break;
        }

 
    }

    printf("*** TO AQUI: '%s'\n", parser->imports->name);
    if (parser->imports != NULL){
        printf("TEM IMPORTACAO");
    }

    return CxTrue;
    
}




