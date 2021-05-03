#ifndef BRICK_H
#define BRICK_H

#include "GameObject.h"
#include "../Physics/BoxCollider.h"
#include "../Physics/PhysicsEntity.h"

class Brick : public GameObject, public PhysicsEntity{
    private:
        bool isSolid;
        bool destroyed;

    public:
        Brick() = default;
        Brick(glm::vec2 position,glm::vec2 size,glm::vec4 color,Texture2D sprite,bool isSolid = false);

        bool isDestroyed();

        void hit(PhysicsEntity* otherEntity) override;
};

#endif 