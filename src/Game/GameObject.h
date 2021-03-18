#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glm/glm.hpp>

#include "../Graphics/SpriteRenderer.h"
#include "../Graphics/Texture2D.h"
#include "../Graphics/Shader.h"

class GameObject{
    protected:
        glm::vec2 position;
        float rotation;
        glm::vec2 size;
        glm::vec3 color;
        glm::vec2 velocity;
        Texture2D sprite;

    public:
        GameObject() = default;
        GameObject(glm::vec2 position,float rotation,glm::vec2 size,glm::vec3 color,glm::vec2 velocity,Texture2D sprite);

        void render(Shader& shader);

        //void cleanup();

        virtual void update(); //Las clases derivadas deben definir este metodo
};

#endif