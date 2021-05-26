#include "Terrain.h"

#include <vector>
#include <time.h> 

#include <glm/gtc/noise.hpp>

void Terrain::generate(int NOColumns,int NORows){
    if(NOColumns <= 0 || NORows <= 0) return;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    ///Genera los vertices e indices necesarios
    float unitWidth = 1.0f/NOColumns;
    float unitHeight = 1.0f/NORows;

    FastNoiseLite noise;
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    noise.SetSeed((int)time(NULL));

        float factorX = 1.0f / NOColumns;
        float factorY = 1.0f / NORows;

        int a = 1,b=2;

    unsigned int numPoints = (NORows +1)*(NOColumns+1);
    for(int j = 0; j<=NORows; j++){
        for(int i = 0; i<=NOColumns; i++){
            float x = unitWidth * i;
            float z = unitHeight * j;

            float result2 = noise.GetNoise((float)i*16.0f,(float)j*16.0f);
            result2 = (result2+1.0f)/2.0f;
            float y = result2*0.15;
            if(z < 0.7 && z >= 0.5){
                float auz = (z-0.5)*5.0f;
                y = (auz*result2*0.15);
            }else if(z < 0.5){
                y = 0.0f;
            }

            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);

            if(j < NORows && i < NOColumns){
                unsigned int indexAct = (j*(NOColumns+1))+ i;
                unsigned int indexUp = ((j+1)*(NOColumns+1)) + i;
                unsigned int indexRight = indexAct+1;
                unsigned int indexRightUp = indexUp+1;

                indices.push_back(indexAct);
                indices.push_back(indexRight);
                indices.push_back(indexRightUp);
                indices.push_back(indexAct);
                indices.push_back(indexUp);
                indices.push_back(indexRightUp);
            }
        }
    }

    NOIndices = indices.size();

    VAO.generate();
    VAO.bind();
        VAO["EBO"] = BufferObject(GL_ELEMENT_ARRAY_BUFFER);
        VAO["EBO"].generate();
        VAO["EBO"].bind();
        VAO["EBO"].setData<GLuint>(indices.size(),&indices[0],GL_STATIC_DRAW);

        VAO["VBO"] = BufferObject(GL_ARRAY_BUFFER);
        VAO["VBO"].generate();
        VAO["VBO"].bind();
        VAO["VBO"].setData<GLfloat>(vertices.size(),&vertices[0],GL_STATIC_DRAW);
        VAO["VBO"].setVertexAttribPointer<GLfloat>(0,3,GL_FLOAT,3,0);
    VAO.unbind();
}

void Terrain::render(Shader& shader){
    shader.activate();
    VAO.bind();
    glDrawElements(GL_TRIANGLES,NOIndices,GL_UNSIGNED_INT,0);
    VAO.unbind();
}

void Terrain::cleanup(){
    VAO.cleanup();
}