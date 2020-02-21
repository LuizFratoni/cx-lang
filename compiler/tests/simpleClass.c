
#include "../cx/lang/aot.h"
#include "../cx/lang/parser.h"


int main(int argc, char ** argv){

    CxBundle bnd = CxCreate_Bundle("SimpleApp", "1.0");
    CxSource src = CxCreate_SourceFromString(bnd, "Codigo 1", "import teste;\n class Janela extends View implements OnOff, Serial { }\n");

    printf("OK Source criado\n");
    CxParser parser;

    printf("Preparando parser\n");
    if ( CxParse_Source(src, &parser) ){
        printf("Parsed with success");
        
    } else {

    }
    return 0;

}



