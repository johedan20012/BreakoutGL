#ifndef MATRIX3D_HPP
#define MATRIX3D_HPP

#include "Vector3D.hpp"

struct Matrix3D {
    private:
        float n[3][3];
    public:

        Matrix3D() = default; //Pone el constructor Matrix3D() como el constructor default

        Matrix3D(float value){ //?MIO
            n[0][0] = value; 
            n[1][1] = value; 
            n[2][2] = value; 
        }

        Matrix3D(float n00, float n01, float n02,
                 float n10, float n11, float n12,
                 float n20, float n21, float n22){
            n[0][0] = n00; n[0][1] = n10; n[0][2] = n20; 
            n[1][0] = n01; n[1][1] = n11; n[1][2] = n21; 
            n[2][0] = n02; n[2][1] = n12; n[2][2] = n22; 
        }

        Matrix3D(const Vector3D& a, const Vector3D& b, const Vector3D& c){
            n[0][0] = a.x; n[0][1] = a.y; n[0][2] = a.z; 
            n[1][0] = b.x; n[1][1] = b.y; n[1][2] = b.z; 
            n[2][0] = c.x; n[2][1] = c.y; n[2][2] = c.z; 
        }

        #ifdef MIDEBUG
        std::string ToString(){
            std::string ret = "";
            
            for(int i=0; i<3; i++){
                ret += "|";
                for(int j=0; j<3; j++){
                    ret += std::to_string(n[i][j]);
                    if(j<2) ret += ",";
                }
                ret += "|\n";
            }

            return ret;
        }
        #endif

        float& operator()(int i,int j){
            return (n[j][i]);
        }

        const float& operator()(int i,int j)const { //El ultimo const dice al compilador que este metodo no modifica al objeto
            return (n[j][i]);
        }

        Vector3D& operator[](int j){
            return (*reinterpret_cast<Vector3D *>(n[j])); // reinterpret_cast es similar a static_cast, excepto que se usa para estructuras y clases
        } 

        const Vector3D& operator[](int j)const{
            return (*reinterpret_cast<const Vector3D *>(n[j]));
        }

        /* Matrix3D& operator +=(const Matrix3D& mat){
            n[0][0] += mat(0,0); n[0][1] += mat(0,1); //...

            return (*this);
        }

        Matrix3D& operator -=(const Matrix3D& mat){
            n[0][0] -= mat(0,0); n[0][1] -= mat(0,1); //...

            return (*this);
        }

        Matrix3D& operator *=(float a){
            n[0][0] *= a; n[0][1] *= a; //...

            return (*this);
        } */
};

Matrix3D operator*(const Matrix3D& A,const Matrix3D& B){
    return Matrix3D(A(0,0)*B(0,0)+A(0,1)*B(1,0)+A(0,2)*B(2,0),
                    A(0,0)*B(0,1)+A(0,1)*B(1,1)+A(0,2)*B(2,1),
                    A(0,0)*B(0,2)+A(0,1)*B(1,2)+A(0,2)*B(2,2),
                    A(1,0)*B(0,0)+A(1,1)*B(1,0)+A(1,2)*B(2,0),
                    A(1,0)*B(0,1)+A(1,1)*B(1,1)+A(1,2)*B(2,1),
                    A(1,0)*B(0,2)+A(1,1)*B(1,2)+A(1,2)*B(2,2),
                    A(2,0)*B(0,0)+A(2,1)*B(1,0)+A(2,2)*B(2,0),
                    A(2,0)*B(0,1)+A(2,1)*B(1,1)+A(2,2)*B(2,1),
                    A(2,0)*B(0,2)+A(2,1)*B(1,2)+A(2,2)*B(2,2));
}

Vector3D operator*(const Matrix3D& A,const Vector3D& v){
    return Vector3D(A(0,0)*v.x+A(0,1)*v.y+A(0,2)*v.z,
                    A(1,0)*v.x+A(1,1)*v.y+A(1,2)*v.z,
                    A(2,0)*v.x+A(2,1)*v.y+A(2,2)*v.z);
}

float Determinant(const Matrix3D& M){
    return (M(0,0)* (M(1,1)*M(2,2)-M(1,2)*M(2,1))
           +M(0,1)* (M(1,2)*M(2,0)-M(1,0)*M(2,2))
           +M(0,2)* (M(1,0)*M(2,1)-M(1,1)*M(2,0)));
}

Matrix3D Inverse(const Matrix3D& M){
    const Vector3D& a = M[0];
    const Vector3D& b = M[1];
    const Vector3D& c = M[2];

    Vector3D r0 = Cross(b,c);
    Vector3D r1 = Cross(c,a);
    Vector3D r2 = Cross(a,b);

    float invDet = 1.0F / Dot(r2,c);

    return Matrix3D(r0.x * invDet, r0.y * invDet, r0.z * invDet,
                    r1.x * invDet, r1.y * invDet, r1.z * invDet,
                    r2.x * invDet, r2.y * invDet, r2.z * invDet);
}

#endif