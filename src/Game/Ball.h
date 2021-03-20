#ifndef BALL_H
#define BALL_H

#include "Player.h"
#include "../Graphics/SpriteManager.h"
#include "../Physics/CircleCollider.h"
#include "../Physics/PhysicsFunctions.h"

//Velocidad inicial de la pelota
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);

class Ball : public GameObject{
    private:
        bool stuck;
        float  diffPosX;
        static Player* player;
        CircleCollider hitbox;

    public:
        Ball() = default;
        Ball(glm::vec2 position,glm::vec2 velocity,Texture2D& sprite);

        CircleCollider& getHitbox();

        void setStuck(bool stuck);
        bool isStuck();

        void update(float deltaTime,unsigned int scrWidth,unsigned int scrHeight);

        void reset(glm::vec2 pos, glm::vec2 vel);

        void hitBrick(BoxCollider& brickHitbox);

        void hitPlayer();

    public:
        //Metodos estaticos
        static void setPlayer(Player* p);
};

#endif
