#ifndef LASER_H
#define LASER_H

#include "GameObject.h"

#include "../Physics/BoxCollider.h"

#include "Player.h"

class Laser : public GameObject{
    private:
        bool active;
        BoxCollider hitbox;

        static Player* player;
    public:
        Laser() = default;
        Laser(Texture2D& sprite);

        BoxCollider& getHitbox();

        bool isActive();

        void launch(glm::vec2 pos);

        void update(float deltaTime);

        void hit();

        static void setPlayer(Player* p);
};

#endif