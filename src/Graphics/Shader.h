#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Math/Vector4D.hpp"

class Shader{
    private:
        unsigned int programId;

    public:
        Shader(const char* vertexShaderFilename,const char* fragmentShaderFilename);

        void activate(); 

        void setInt(const char*name,int val);
        void setFloat3(const char* name,float f1,float f2,float f3);
        void setFloat3(const char* name,glm::vec3 vec);
        void setFloat4(const char* name,float f1,float f2,float f3,float f4);
        void setFloat4(const char* name,Vector4D vec);
        void setFloatMat4(const char* name,glm::mat4 mat);

        void cleanup();

    private:
        std::string loadShaderScr(const char* filename);

        unsigned int compileShader(const char* shaderFilename,GLenum type);
};
#endif