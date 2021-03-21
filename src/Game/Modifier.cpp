#include "Modifier.h"

Modifier::Modifier(glm::vec2 position,glm::vec2 velocity,ModifierType type,Texture2D& sprite)
    :GameObject(position,0,glm::vec2(50.0f,50.0f),glm::vec4(1.0f),velocity,sprite)
    ,type(type),active(true){
        hitbox = BoxCollider(position,glm::vec2(50.0f,50.0f));
}

BoxCollider& Modifier::getHitbox(){
    return hitbox;
}

ModifierType Modifier::getType(){
    return type;
}

bool Modifier::isActive(){
    return active;
}

void Modifier::desactivate(){
    active = false;
}

void Modifier::update(float deltaTime){
    if(active){
        position += velocity*deltaTime;
        if(position.x < 0.0f){
            position.x = 0.0f;
            velocity.x *= -1;
        }else if(position.x+size.x > 800.0f){
            position.x = 800.0f-size.x;
            velocity.x *= -1;
        }

        if(position.y > 600.0f){
            active = false;
        }
    }

    hitbox.moveTo(position);
}