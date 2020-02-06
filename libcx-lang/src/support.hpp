
#ifndef _CX_SUPPORT_HPP
#define _CX_SUPPORT_HPP


#include <support.h>

namespace Cx {
    class Object {
    protected:
        CxObj self;

    protected:

        inline void init(CxObj obj){
            if (self != 0) CxRelease(self);
            self = obj;
            if (self != 0) CxAddRef(self);
        }

    public:

        Object(){

        }

        Object(const Object &o){
            if (self != 0) CxRelease(self);
            self = o.self;
            if (self != 0) CxAddRef(self);
        }

        ~Object(){
            if (self != 0) CxRelease(self);
        }

        bool cast(const char* type, Object &result){
            if (self == 0) return false;
            CxObj ro;
            CxCast(self, type, &ro);
            result.init(ro);
            return true;
        }
    };

    class String : public Object {
    public:

        
    };

}


#endif

