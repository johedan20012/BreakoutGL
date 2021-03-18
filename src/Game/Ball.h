#ifndef BALL_H
#define BALL_H

#include "Player.h"

class Ball : public GameObject{
    private:
        bool isStuck;

        Player* player; //Esto causara problemas eventualmente, pero funciona
    
    public:
        Ball() = default;
        Ball(glm::vec2 position,glm::vec2 velocity,Player* player,Texture2D& sprite);

        void setStuck(bool stuck);

        void update(float deltaTime,unsigned int scrWidth,unsigned int scrHeight);

        void reset(glm::vec2 pos, glm::vec2 vel);
};

#endif
