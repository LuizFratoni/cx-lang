
#include "../parser.h"


#define IS_ALPHA(parser) (parser->curCh >= 65 && parser->curCh <= 90) || (parser->curCh >= 97 && parser->curCh <= 122) 
#define IS_ALPHA_NUMERIC(parser) (parser->curCh >= 65 && parser->curCh <= 90) || (parser->curCh >= 97 && parser->curCh <= 122) || (parser->curCh >= 48 && parser->curCh <= 57)


CxBool  CxParse_Statement(CxParser parser, CxStatement *result){

    CxStatement first, last, cur;
    first = NULL; last = NULL;
    CxExpression exp = NULL;
    CxBool resultb = CxTrue;


    do {
        if ( IS_ALPHA(parser->curCh)){
            if (exp == NULL){

            } else {
                CxParse_Error(parser, "Too much identifiers - Separate variables with comma", ' ');
                CxTk_NextLine(parser);
                resultb= CxFalse;
            }
        } else {
            if (parser->curCh == '='){

            } else if (parser->curCh == '.'){
                if (exp == NULL){
                    CxParse_Error(parser, "Invalid operator . at this position", ' ');
                    CxTk_Next(parser);
                    CxTk_NextLine(parser);
                    resultb= CxFalse;    
                } else {
                    
                }
            } else if (parser->curCh == ')'){
                 
            } else if (parser->curCh == ';'){
                CxParse_Error(parser, "Statement closed without content", ' ');
                CxTk_Next(parser);
                CxTk_NextLine(parser);
                resultb= CxFalse;
            } else {
                CxParse_Error(parser, "Expecting Statemente but '%c' Found", parser->curCh);
                CxTk_NextLine(parser);
                resultb= CxFalse;
            }
        }
    }

    *result = first;

    return resultb;

}