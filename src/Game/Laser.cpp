#include "Laser.h"

Laser::Laser(Texture2D& sprite)
    :GameObject(glm::vec2(0.0f),0,glm::vec2(15.0f,25.0f),glm::vec4(1.0f),glm::vec2(0.0f,-550.0f),sprite)
    ,active(false),hitbox(BoxCollider(glm::vec2(0.0f),glm::vec2(15.0f,25.0f))){}

BoxCollider& Laser::getHitbox(){
    return hitbox;
}

bool Laser::isActive(){
    return active;
}

void Laser::launch(glm::vec2 pos){
    active = true;
    position = pos;
    hitbox.moveTo(position);
}

void Laser::update(float deltaTime){
    if(!active) return;
    position += velocity*deltaTime;
    if(position.y < 0){
        active = false;
    }

    hitbox.moveTo(position);
}

void Laser::hit(){
    active = false;
}