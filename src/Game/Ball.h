#ifndef BALL_H
#define BALL_H

#include <glm/gtx/rotate_vector.hpp>

#include "Player.h"
#include "../Graphics/SpriteManager.h"
#include "../Physics/CircleCollider.h"
#include "../Physics/PhysicsFunctions.h"
#include "../Physics/PhysicsEntity.h"

//Velocidad inicial de la pelota
const glm::vec2 INITIAL_BALL_VELOCITY_DIR(0.2f, -0.961f);
const float MAX_BALL_VELOCITY = 1000.0f;

class Ball : public GameObject, public PhysicsEntity{
    private:
        bool stuck;
        float  diffPosX;
        float velMagnitude;
        static Player* player;
        bool dead;

    public:
        Ball() = default;
        Ball(glm::vec2 position,float velMagnitude,Texture2D& sprite); //velMagnitude es 364 para el default

        void setStuck(bool stuck);
        bool isStuck();

        void update(float deltaTime,unsigned int scrWidth,unsigned int scrHeight);

        void reset(float velMag);

        void hit(PhysicsEntity* otherEntity) override;

        void applyModifier(ModifierType modifier);

        bool isDead();

    private:

        void hitPlayer();

        void hitBrick(BoxCollider* brickHitbox);

    public:
        //Metodos estaticos
        static void setPlayer(Player* p);
};

#endif
