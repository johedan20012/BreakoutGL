#ifndef LASER_H
#define LASER_H

#include "GameObject.h"

#include "../Physics/PhysicsEntity.h"
#include "../Physics/PhysicsManager.h"

class Laser : public GameObject, public PhysicsEntity{
    private:
        bool active;
    public:
        Laser() = default;
        Laser(Texture2D& sprite);
        ~Laser();

        void init();

        bool isActive();

        void launch(glm::vec2 pos);

        void update(float deltaTime);

        void hit(PhysicsEntity* otherEntity);
};

#endif