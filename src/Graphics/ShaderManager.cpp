#include "ShaderManager.h"

std::map<std::string,Shader> ShaderManager::shaders;

void ShaderManager::loadShader(const char* vertexShaderFilename,const char* fragmentShaderFilename,std::string name){
    if(shaders.count(name) > 0) return;

    shaders[name].load(vertexShaderFilename,fragmentShaderFilename);
}

Shader& ShaderManager::getShader(std::string name){
    return shaders[name];
}

void ShaderManager::clearShader(std::string name){
    if(shaders.count(name) <= 0) return;
    shaders[name].cleanup();
    shaders.erase(name);
}

void ShaderManager::cleanup(){
    for(auto& pair : shaders){
        pair.second.cleanup();
    }

    shaders.clear();
}