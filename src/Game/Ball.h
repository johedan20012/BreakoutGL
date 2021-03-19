#ifndef BALL_H
#define BALL_H

#include "Player.h"
#include "../Physics/PhysicsObject.h"


#include "../Graphics/SpriteManager.h"


class Ball : public PhysicsObject{
    private:
        bool isStuck;
    public: //No mires este atributo publico
        static Player* player; //Esto causara problemas eventualmente, pero funciona
    
    public:
        Ball() = default;
        Ball(glm::vec2 position,glm::vec2 velocity,Texture2D& sprite);

        void setStuck(bool stuck);

        void update(float deltaTime,unsigned int scrWidth,unsigned int scrHeight);

        void reset(glm::vec2 pos, glm::vec2 vel);

        void hit(PhysicsObject& other)override;
        
};

#endif
