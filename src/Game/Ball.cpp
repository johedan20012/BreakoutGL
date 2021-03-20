#include "Ball.h"

Player* Ball::player = nullptr;

Ball::Ball(glm::vec2 position,glm::vec2 velocity,Texture2D& sprite)
    : GameObject(position,0,glm::vec2(12.0f,12.0f),glm::vec3(1.0f),velocity,sprite)
    ,diffPosX(0.5f), stuck(true){
    hitbox = CircleCollider(position,6.0f);
}

CircleCollider& Ball::getHitbox(){
    return hitbox;
}

void Ball::setStuck(bool stuck){
    this->stuck = stuck;
}

bool Ball::isStuck(){
    return stuck;
}

void Ball::update(float deltaTime,unsigned int scrWidth,unsigned int scrHeight){
    if(!stuck){ //Actualiza la pelota si no esta atorada
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
        float posX = diffPosX*(player->getSize().x-size.x);
        position = player->getPosition()+glm::vec2(posX,-size.y);
    }

    hitbox.moveTo(position);
}

void Ball::reset(glm::vec2 pos,glm::vec2 vel){
    position = pos;
    velocity = vel;
}

void Ball::hitBrick(BoxCollider& brickHitbox){
    glm::vec2 center = hitbox.calculateCenter();
    glm::vec2 centerOther = brickHitbox.calculateCenter();
    glm::vec2 halfDimOther = brickHitbox.calculateDimensions() / 2.0f;
    
    glm::vec2 difference = hitbox.calculateCenter() - brickHitbox.calculateCenter();
    glm::vec2 clamped = glm::clamp(difference, -halfDimOther,halfDimOther);
    glm::vec2 closest = centerOther + clamped;
    difference = closest - center;
    
    float radius = hitbox.calculateDimensions().x / 2.0f;

    glm::vec2 dirDiff = Physics::DirectionVector(difference);
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

    hitbox.moveTo(position);
}

void Ball::hitPlayer(){
    if(player->isSticky() && velocity.y > 0){ //Si el jugador es pegajoso y la pelota esta cayendo, entonces la pelota se pega
        diffPosX = (position.x-player->getPosition().x) / (player->getSize().x-size.x);

        stuck = true;
    }

    glm::vec2 playerCenter = player->getHitbox().calculateCenter();
    glm::vec2 playerSize = player->getHitbox().calculateDimensions();
    glm::vec2 center = hitbox.calculateCenter();
    //glm::vec2 playerPos = playerCenter - (playerSize/2.0f);
    float distance = center.x - playerCenter.x;
    float percentage = distance / (playerSize.x / 2.0f);

    float strength = 2.0f;
    glm::vec2 oldVelocity = velocity;
    velocity.x = INITIAL_BALL_VELOCITY.x * percentage * strength;
    velocity.y = -1.0f * abs(velocity.y);  
    velocity = glm::normalize(velocity) * glm::length(oldVelocity);
}

void Ball::setPlayer(Player* p){
    player = p;
}