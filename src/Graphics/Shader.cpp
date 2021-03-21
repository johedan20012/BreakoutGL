#include "Shader.h"

Shader::Shader(const char* vertexShaderFilename,const char* fragmentShaderFilename){
    int success;
    char infoLog[512];
    //Crear el vertex y fragment shader
    unsigned int vertexShader,fragmentShader;
    
    vertexShader = compileShader(vertexShaderFilename,GL_VERTEX_SHADER);
    fragmentShader = compileShader(fragmentShaderFilename,GL_FRAGMENT_SHADER);

    //Creación del shader program , es la union de todo los shaders, en este caso del fragment y vertex shader
    programId = glCreateProgram();

    glAttachShader(programId,vertexShader); //Se unen los dos shaders al programa
    glAttachShader(programId,fragmentShader);
    glLinkProgram(programId); //Se linkea el shader program

    glGetProgramiv(programId,GL_LINK_STATUS,&success);
    if(!success){
        glGetProgramInfoLog(programId,512,NULL,infoLog);
        std::cout<<"Error al linkear el shader program:\n"<<infoLog<<"\n";
    }

    //Eliminar los shaders, pues ya no son necesarios
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::activate(){
    glUseProgram(programId);
}

void Shader::setInt(const char*name,int val){
    glUniform1i(glGetUniformLocation(programId,name),val);
}

void Shader::setFloat3(const char* name,float f1,float f2,float f3){
    glUniform3f(glGetUniformLocation(programId,name),f1,f2,f3);
}

void Shader::setFloat3(const char* name,glm::vec3 vec){
    setFloat3(name,vec.x,vec.y,vec.z);
}   

void Shader::setFloat4(const char* name,float f1,float f2,float f3, float f4){
    glUniform4f(glGetUniformLocation(programId,name),f1,f2,f3,f4);
}

void Shader::setFloat4(const char* name, glm::vec4 vec){
    setFloat4(name,vec.x,vec.y,vec.z,vec.w);
}

void Shader::setFloat4(const char* name,Vector4D vec){
    setFloat4(name,vec.x,vec.y,vec.z,vec.w);
}

void Shader::setFloatMat4(const char* name,glm::mat4 mat){
    glUniformMatrix4fv(glGetUniformLocation(programId, name), 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::cleanup(){
    glDeleteProgram(programId);
}

std::string Shader::loadShaderScr(const char* filename){
    std::ifstream file;
    std::stringstream buffer;

    std::string ret = "";

    file.open(filename);

    if(file.is_open()){
        buffer << file.rdbuf();
        ret = buffer.str();
    }else{
        std::cout<<"No se pudo abrir el archivo "<<filename<<"\n";
    }
    file.close();
    return ret;
}

unsigned int Shader::compileShader(const char* shaderFilename,GLenum type){
    int success;
    char infoLog[512];
    unsigned int shader;
    
    shader = glCreateShader(type);
    std::string shaderSrc = loadShaderScr(shaderFilename);
    const GLchar* shaderScr = shaderSrc.c_str();
    glShaderSource(shader,1,&shaderScr,NULL);

    glCompileShader(shader);

    glGetShaderiv(shader,GL_COMPILE_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(shader,512,NULL,infoLog);
        std::cout<<"Error al compilar el shader:\n"<<infoLog<<"\n"<<shaderFilename<<"\n";
    }

    return shader;
}