#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP

#include <math.h>
#include <string>

struct Vector3D{
    float x,y,z;

    Vector3D() = default;

    Vector3D(float a,float b,float c){
        x = a;
        y = b;
        z = c;
    }

    #ifdef MIDEBUG
    std::string ToString(){ 
        return "("+std::to_string(x)+","+std::to_string(y)+","+std::to_string(z)+")";
    }
    #endif

    float& operator [](int i){
        return ((&x)[i]); //Talvez esta no es la forma ya que x,y,z no simempre estaran juntos en memoria
    }

    const float& operator [](int i) const{
        return ((&x)[i]);
    }

    Vector3D& operator *=(float s){
        x *= s;
        y *= s;
        z *= s;
        return (*this);
    }

    Vector3D& operator /=(float s){
        s = 1.0F /s;
        x *= s;
        y *= s;
        z *= s;
        return (*this);
    }

    Vector3D& operator +=(const Vector3D& v){
        x += v.x;
        y += v.y;
        z += v.z;
        return (*this);
    }

    Vector3D& operator -=(const Vector3D& v){
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return (*this);
    }
};

/* 
    La palabra reservada "inline" le indica al compilador que la funcion sea "pegada" en cada lugar donde es llamada 
    esto puede ser ignorado por el compilador, y se usa principalmente para funciones pequeñas.
*/
inline Vector3D operator +(const Vector3D& v, const Vector3D& v2){
    return Vector3D(v.x+v2.x,v.y+v2.y,v.z+v2.z);
}

inline Vector3D operator -(const Vector3D& v, const Vector3D& v2){
    return Vector3D(v.x-v2.x,v.y-v2.y,v.z-v2.z);
}

inline Vector3D operator *(const Vector3D& v,float s){
    return (Vector3D(v.x*s,v.y*s,v.z*s));
}

inline Vector3D operator /(const Vector3D& v, float s){
    s = 1.0f / s;
    return Vector3D(v.x*s,v.y*s,v.z*s);
}

inline Vector3D operator -(const Vector3D& v){
    return Vector3D(-v.x,-v.y,-v.z);
}

inline float Magnitude(const Vector3D& v){
    return sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
}

inline Vector3D Normalize(const Vector3D& v){ //Asumir que ||v|| != 0, esta funcion puede ser más rapida con fast inverse square root de Quake 3
   return (v/Magnitude(v));
}

inline float Dot(const Vector3D& v, const Vector3D& v2){
    return v.x*v2.x + v.y*v2.y + v.z*v2.z; //Propiedad del producto punto : a.b = ||a||||b||cos\thetha, donde \thetha es el angulo planar entre los vectores a y b
}

inline Vector3D Cross(const Vector3D& v,const Vector3D& v2){
    return Vector3D(v.y*v2.z - v.z*v2.y,
                    v.z*v2.x - v.x*v2.z,
                    v.x*v2.y - v.y*v2.x);
}

inline Vector3D Project(const Vector3D& v, const Vector3D& v2){
    return (v* (Dot(v,v) / Dot(v2,v2)));
}

inline Vector3D Reject(const Vector3D& v,const Vector3D& v2){
    return v-Project(v,v2); //El libro pone las operaciones directo envez de usar project(v,v2)
}

#endif