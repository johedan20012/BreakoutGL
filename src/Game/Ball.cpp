#include "Ball.h"

Ball::Ball(glm::vec2 position,glm::vec2 velocity,Player* player,Texture2D& sprite)
    : GameObject(position,0,glm::vec2(25.0f,25.0f),glm::vec3(1.0f),velocity,sprite),player(player), isStuck(true){}

void Ball::setStuck(bool stuck){
    isStuck = stuck;
}

void Ball::update(float deltaTime,unsigned int scrWidth,unsigned int scrHeight){
    if(!isStuck){ //Actualiza la pelota si no esta atorada
        position += velocity * deltaTime;
        if(position.x+size.x > scrWidth){
            position.x = scrWidth-size.x;
            velocity.x *= -1;
        }else if(position.x < 0){
            position.x = 0.0f;
            velocity.x *= -1;
        }

        if(position.y < 0){
            position.y = 0;
            velocity.y *= -1;
        }

        //TODO Checar colición con la barra del jugador y los ladrillos
    }else{
        position = player->getPosition()+glm::vec2(player->getSize().x/2.0f - 12.5f,-25.0f);
    }
}

void Ball::reset(glm::vec2 pos,glm::vec2 vel){
    position = pos;
    velocity = vel;
}