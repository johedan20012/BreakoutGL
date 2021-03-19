#ifndef BRICK_H
#define BRICK_H

#include "../Physics/PhysicsObject.h"

class Brick : public PhysicsObject{
    private:
        bool isSolid;
        bool destroyed;

    public:
        Brick() = default;
        Brick(glm::vec2 position,glm::vec2 size,glm::vec3 color,Texture2D sprite,bool isSolid = false);

        bool isDestroyed();

        void hit(PhysicsObject& other)override;
};

#endif 