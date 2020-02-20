

#include <stdio.h>
#include <string.h>

#include "cx/lang/aot.h"

#include "cx/lang/parser.h"


int main(int argc, char** argv){

    CxObj bundle = CxNew_Bundle("mymodule", "MOdule de Teste", "1.0");

    
    
    CxBundle_CreateClass(bundle, "Alpha");
}