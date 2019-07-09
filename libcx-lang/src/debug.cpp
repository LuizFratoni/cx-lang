
#include "lang.h"
#include "CxClass.hpp"
#include <stdlib.h>

void iniciarBundle(Cx::Bundle b){
     b.createClass("alpha beta");
}

int main(){

    printf("Inicializando via CPP\n");

    Cx::Bundle bundle("Teste");

    iniciarBundle(bundle);

    return 0;
}