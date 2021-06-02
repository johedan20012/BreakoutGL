#ifndef SPRITE_H
#define SPRITE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include "Texture2D.h"
#include "GlMemory.hpp"

class SpriteRenderer{
    private:
        static ArrayObject VAO;
    public:
        static void init();

        static void drawSprite(Texture2D& texture,Shader& shader,
            glm::vec2 pos,glm::vec2 size = glm::vec2(10.0f,10.0f), 
            float rotate = 0.0f, glm::vec4 color = glm::vec4(1.0f));

        static void drawSprite3D(Texture2D& texture,Shader& shader,
            glm::vec3 pos,glm::vec3 size = glm::vec3(10.0f,10.0f,0.0f), 
            float rotate = 0.0f,glm::vec3 rotationVector = glm::vec3(0.0f,0.0f,1.0f), glm::vec4 color = glm::vec4(1.0f));

        static void cleanup();
    private:
        SpriteRenderer();
};

#endif