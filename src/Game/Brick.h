#ifndef BRICK_H
#define BRICK_H

#include "GameObject.h"
#include "Player.h"

#include "../Physics/BoxCollider.h"
#include "../Physics/PhysicsEntity.h"
#include "../Physics/PhysicsManager.h"

class Brick : public GameObject, public PhysicsEntity{
    private:
        bool isSolid;
        bool destroyed;
        bool spawnModifier;

        glm::vec2 cellPos;

        static Player* player;
    public:
        Brick(glm::vec2 position,glm::vec2 cellPos,glm::vec2 size,glm::vec4 color,Texture2D sprite,bool isSolid = false);
        ~Brick();

        bool isDestroyed();
        bool shouldSpawnModifier();

        glm::vec2 getCellPos();

        void hit(PhysicsEntity* otherEntity) override;
    public: // Metodos estaticos
        static void setPlayer(Player* p);
};

#endif 