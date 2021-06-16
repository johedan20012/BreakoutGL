#ifndef GLMEMORY_HPP
#define GLMEMORY_HPP

#include <glad/glad.h>
#include <iostream>
#include <map>

class BufferObject{
    private:
        unsigned int bufferId;

        GLenum type;
    public:
        BufferObject(){}
        BufferObject(GLenum type)
            :type(type){
        }
        //Default destructor

        void generate(){
            glGenBuffers(1,&bufferId);
        }

        /*OpenGl asegura que minimo podremos contar con 16 vertex attributes, pero dependiendo de la GPU se pueden contar con mas 
         --Ese número se consulta asi:
            int nrAttributes;
            glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
            std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
        */
        template<typename T>
        void setVertexAttribPointer(GLuint index,GLint size,GLenum typeOfData,GLuint stride,GLuint offset){
            glVertexAttribPointer(index,size,typeOfData,GL_FALSE,stride*sizeof(T),(void*)(offset*sizeof(T)));
            glEnableVertexAttribArray(index);
        }

        template<typename T>
        void setData(GLuint noElements,T* data,GLenum usage){
            //Se copia los datos de los vertices al buffer "actual"
            glBufferData(type,noElements*sizeof(T),data,usage);
        }

        template<typename T>
		void updateData(GLintptr offset, GLuint noElements, T*data) {
			glBufferSubData(type, offset, noElements * sizeof(T), data);
		}

        template<typename T>
        void setSubData(GLuint noElements,GLint offset,T* data){
            glBufferSubData(type,offset,sizeof(T)*noElements,data);
        }

        void bind(){
            glBindBuffer(type,bufferId);
        }

        void unbind(){
            glBindBuffer(type,0);
        }

        void cleanup(){
            glDeleteBuffers(1,&bufferId);
        }
};

class ArrayObject{
    private:
        unsigned int arrayId;

        std::map<std::string,BufferObject> buffers;
    public:
        ArrayObject(){}

        void generate(){
            //Creacion del Vertex Array Object
            //El VAO guarda las llamadas a glEnableVertexAttribArray o glDisableVertexAttribArray.
            //Configuraciones como glVertexAttribPointer.
            //Y VBO asociados con las llamadas de glVertexAttribPointer.
            glGenVertexArrays(1,&arrayId);
        }
    
        BufferObject& operator[](const char* key){
            return buffers[key];
        }

        void bind(){
            glBindVertexArray(arrayId);
        }

        void unbind(){
            glBindVertexArray(0);
        }

        void cleanup(){
            for(auto& pair : buffers){
                pair.second.cleanup();
            }
            glDeleteVertexArrays(1,&arrayId);
        }
};

#endif