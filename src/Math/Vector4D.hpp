#ifndef VECTOR4D_HPP
#define VECTOR4D_HPP

#include <string>

struct Vector4D{
    float x,y,z,w;

    Vector4D() = default;

    Vector4D(float c1,float c2,float c3, float c4){
        x = c1;
        y = c2;
        z = c3;
        w = c4;
    }

    #ifdef MIDEBUG
    std::string ToString(){ 
        return "("+std::to_string(x)+","+std::to_string(y)+","+std::to_string(z)+","+std::to_string(w)+")";
    }
    #endif
};

#endif