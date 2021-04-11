#include "Ball.h"

Player* Ball::player = nullptr;

Ball::Ball(glm::vec2 position,float velMagnitude,Texture2D& sprite)
    : GameObject(position,0,glm::vec2(12.0f,12.0f),glm::vec4(1.0f),INITIAL_BALL_VELOCITY_DIR,sprite)
    ,diffPosX(0.5f),velMagnitude(velMagnitude), stuck(true){
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
        position += velMagnitude * velocity * deltaTime;
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

void Ball::reset(glm::vec2 pos,float velMag){
    position = pos;
    velocity = INITIAL_BALL_VELOCITY_DIR;
    velMagnitude = velMag;
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

    velMagnitude *= 1.01f;
    if(velMagnitude > MAX_BALL_VELOCITY){
        velMagnitude = MAX_BALL_VELOCITY;
    }

    hitbox.moveTo(position);
}

void Ball::hitPlayer(){
    float diff = (position.x-player->getPosition().x) / (player->getSize().x-size.x);
    diff = glm::clamp(diff,0.0f,1.0f);// diff \in [-1,1]

    if(player->isSticky() && velocity.y > 0){ //Si el jugador es pegajoso y la pelota esta cayendo, entonces la pelota se pega
        diffPosX = (position.x-player->getPosition().x) / (player->getSize().x-size.x);

        stuck = true;
    }
    float angle = (diff*150.0f)+15.0f;
    glm::vec3 newVelocityDir = glm::rotate(glm::vec3(-1.0f,0.0f,0.0f),glm::radians(angle),glm::vec3(0.0f,0.0f,1.0f));

    velocity.x = newVelocityDir.x;
    velocity.y = newVelocityDir.y;
    velocity = glm::normalize(velocity);
}

void Ball::applyModifier(ModifierType modifier){
    switch (modifier) {
        case ModifierType::FAST_BALL:
            velMagnitude = MAX_BALL_VELOCITY;
            break;
        
        case ModifierType::SLOW_BALL:
            velMagnitude = 364.0f;
            break;
        
        case ModifierType::THROUGH_BALL:
            //FIXME
            break;
        
        case ModifierType::FIRE_BALL:
            //FIXME
            break;
    }
}

void Ball::setPlayer(Player* p){
    player = p;
}