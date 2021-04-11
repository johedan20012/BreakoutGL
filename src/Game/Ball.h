#ifndef BALL_H
#define BALL_H

#include <glm/gtx/rotate_vector.hpp>

#include "Player.h"
#include "../Graphics/SpriteManager.h"
#include "../Physics/CircleCollider.h"
#include "../Physics/PhysicsFunctions.h"

//Velocidad inicial de la pelota
const glm::vec2 INITIAL_BALL_VELOCITY_DIR(0.2f, -0.961f);
const float MAX_BALL_VELOCITY = 1000.0f;

class Ball : public GameObject{
    private:
        bool stuck;
        float  diffPosX;
        float velMagnitude;
        static Player* player;
        CircleCollider hitbox;

    public:
        Ball() = default;
        Ball(glm::vec2 position,float velMagnitude,Texture2D& sprite); //velMagnitude es 364 para el default

        CircleCollider& getHitbox();

        void setStuck(bool stuck);
        bool isStuck();

        void update(float deltaTime,unsigned int scrWidth,unsigned int scrHeight);

        void reset(glm::vec2 pos, float velMag);

        void hitBrick(BoxCollider& brickHitbox);

        void hitPlayer();

        void applyModifier(ModifierType modifier);

    public:
        //Metodos estaticos
        static void setPlayer(Player* p);
};

#endif
