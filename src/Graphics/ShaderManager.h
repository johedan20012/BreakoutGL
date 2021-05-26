#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <map>

#include "Shader.h"

class ShaderManager{
    private:
        static std::map<std::string,Shader> shaders;

    public:
        static void loadShader(const char* vertexShaderFilename,const char* fragmentShaderFilename,std::string name);
        static void loadShader(const char* vertexShaderFilename,const char* fragmentShaderFilename,const char* geometryShaderFilename,std::string name);

        static Shader& getShader(std::string name);

        void clearShader(std::string name);

        static void cleanup();
    private:
        ShaderManager();
};

#endif