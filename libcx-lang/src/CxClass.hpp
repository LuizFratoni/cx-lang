

#ifndef _CX_CLASS_HPP_
#define _CX_CLASS_HPP_

#include "lang.h"
#include <stdio.h>


namespace Cx {

    class Bundle {
    protected:
        CxObj obj;
    
    public:

        Bundle(const char* name){
            printf("Iniciando CxBundle with Name: %s\n");
            obj = CxObjects_NewBundle(name);
            printf("Bundle Criado\n\n");
        }   

        Bundle(const Bundle &bundle){
            if (obj != 0) CxObj_Release(obj);
            if (bundle.obj != 0){
                obj = bundle.obj;
                CxObj_AddRef(obj);
            }
        }

        ~Bundle(){
            if (obj != 0)
                CxObj_Release(obj);
        }

        void createClass(const char* name){
            CxBundle_CreateClass(obj, name);
        }


    };


    class Class {
    protected:
        CxObj obj;
    public:

 
    };  

}

#endif