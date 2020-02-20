
#include "cx/lang/aot.h"



int main(int argc, char ** argv){

    CxBundle bnd = CxCreate_Bundle("SimpleApp", "bla bla bla", "1.0");
    CxSource src = CxCreate_SourceFromString(bnd, "Codigo 1", "import teste;\n class Improviso { }\n");

    CxParser parser;

    if ( CxParse_Source(src, &parser) ){
        printf("Parsed with success");
        
    } else {

    }
    return 0;
}



