#include "Ball.h"

Player* Ball::player = nullptr;

Ball::Ball(glm::vec2 position,glm::vec2 velocity,Texture2D& sprite)
    : PhysicsObject(position,0,glm::vec2(25.0f,25.0f),glm::vec3(1.0f),velocity,sprite,new CircleCollider(position,12.5f)), isStuck(true){
        
    }

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
    }else{
        position = player->getPosition()+glm::vec2(player->getSize().x/2.0f - 12.5f,-25.0f)+glm::vec2(0.0f,-15.0f);
    }

    updateHitbox(position);
}

void Ball::reset(glm::vec2 pos,glm::vec2 vel){
    position = pos;
    velocity = vel;
}

void Ball::hit(PhysicsObject& other){
    glm::vec2 center = hitbox->calculateCenter();
    glm::vec2 centerOther = other.getHitbox()->calculateCenter();
    glm::vec2 halfDimOther = other.getHitbox()->calculateDimensions() / 2.0f;
    
    glm::vec2 difference = hitbox->calculateCenter() - other.getHitbox()->calculateCenter();
    glm::vec2 clamped = glm::clamp(difference, -halfDimOther,halfDimOther);
    glm::vec2 closest = centerOther + clamped;
    difference = closest - center;
    
    float radius = hitbox->calculateDimensions().x / 2.0f;

    glm::vec2 dirDiff = directionVector(difference);
    if (dirDiff.x == 1.0f || dirDiff.x == -1.0f) {
        velocity.x *= -1;

        float penetration = radius - std::abs(difference.x);
        if (dirDiff.x == -1.0f){
            position.x += penetration;
        }else{
            position.x -= penetration; 
        }
    }else{
        velocity.y *= -1;

        float penetration = radius - std::abs(difference.y);
        if (dirDiff.y == 1.0f){
            position.y -= penetration;
        }else{
            position.y += penetration;
        }
    }
}