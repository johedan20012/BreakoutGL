#ifndef BRICK_H
#define BRICK_H

#include "GameObject.h"

class Brick : public GameObject{
    private:
        bool isSolid;

    public:
        Brick() = default;
        Brick(glm::vec2 position,glm::vec2 size,glm::vec3 color,Texture2D sprite,bool isSolid = false);
};

#endif 