#include "Player.h"

Player::Player(Texture2D& sprite)
    : GameObject(glm::vec2(350.0f,580.0f),0,glm::vec2(100.0f,20.0f),glm::vec3(1.0),glm::vec2(500.0f,0.0f),sprite)
    , lives(3),isSticky(false),hasLasers(false),sizeBar(1),score(0){ 
        hitbox = BoxCollider(glm::vec2(350.0f,580.0f),glm::vec2(100.0f,20.0f));
}

BoxCollider& Player::getHitbox(){
    return hitbox;
}

void Player::update(float deltaTime){
    //Manejar la entrada
    handleInput(deltaTime);

    hitbox.moveTo(position);
}

void Player::addScore(unsigned int points){
    score += points;
}

unsigned int Player::getScore(){
    return score;
}

void Player::applyModifier(PlayerModifier modifier){
    switch (modifier)
    {
        case PlayerModifier::LARGE_BAR:
            sizeBar++;
            if(sizeBar > 4)sizeBar = 4;
            break;
        
        case PlayerModifier::SHORT_BAR:
            sizeBar = 0;
            break;

        case PlayerModifier::STICKY_BAR:
            isSticky = true;
            break;

        case PlayerModifier::LASER_BAR:
            hasLasers = true;
            break;
        case PlayerModifier::RESET_BAR:
            isSticky = false;
            hasLasers = false;
            sizeBar = 1;
    }
}

void Player::handleInput(float deltaTime){
    float realXVelocity = velocity.x * deltaTime;

    if(Keyboard::key(GLFW_KEY_LEFT) == GLFW_PRESS || Keyboard::key(GLFW_KEY_A) == GLFW_PRESS){
        //Mover a la izquierda
        position.x -= realXVelocity;
        if(position.x < 0.0f){
            position.x = 0.0f;
        }
    }

    if(Keyboard::key(GLFW_KEY_RIGHT) == GLFW_PRESS || Keyboard::key(GLFW_KEY_D) == GLFW_PRESS){
        //Mover a la derecha
        position.x += realXVelocity;
        if(position.x > 800.0f-size.x){
            position.x = 800.0f-size.x;
        }
    }
}