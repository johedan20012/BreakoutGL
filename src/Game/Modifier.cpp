#include "Modifier.h"

#include "Level.h"

Level* Modifier::level = nullptr;

Modifier::Modifier(glm::vec2 position,glm::vec2 velocity,ModifierType type,Texture2D& sprite)
    :GameObject(position,0,glm::vec2(50.0f,50.0f),glm::vec4(1.0f),velocity,sprite)
    ,PhysicsEntity(new BoxCollider(position,glm::vec2(50.0f,50.0f)),EntityType::MODIFIER,(unsigned int)(EntityType::BRICK))
    ,modType(type),active(true){
        id = PhysicsManager::registerEntity(this);
}

Modifier::~Modifier(){
    PhysicsManager::unregisterEntity(id);
}

ModifierType Modifier::getModType(){
    return modType;
}

bool Modifier::isActive(){
    return active;
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

        hitbox->moveTo(position);
    }
}

void Modifier::hit(PhysicsEntity* otherEntity){
    level->applyModifier(modType);
    active = false;
}

void Modifier::setLevel(Level* l){
    level = l;
}