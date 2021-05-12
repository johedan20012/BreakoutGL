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
        bool explode;

        int resistance;

        static Player* player;
    public:
        Brick(glm::vec2 position,glm::vec2 size,int resistance,Texture2D sprite,bool isSolid = false);
        ~Brick();

        void destroy();

        bool isDestroyed();
        bool shouldSpawnModifier();
        bool shouldExplode();

        void hit(PhysicsEntity* otherEntity) override;
    private:
        void updateColor();
    
    public: // Metodos estaticos
        static void setPlayer(Player* p);
};

#endif 