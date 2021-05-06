#include "Laser.h"

Laser::Laser(Texture2D& sprite)
    :GameObject(glm::vec2(0.0f),0,glm::vec2(15.0f,25.0f),glm::vec4(1.0f),glm::vec2(0.0f,-550.0f),sprite)
    ,PhysicsEntity(new BoxCollider(glm::vec2(0.0f),glm::vec2(15.0f,25.0f)),EntityType::LASER,(unsigned int)(EntityType::BRICK))
    ,active(true){
        ignoreCollisions = true;
    }

Laser::~Laser(){
    if(id!=0) PhysicsManager::unregisterEntity(id);
}

void Laser::init(){
    id = PhysicsManager::registerEntity(this);
}

bool Laser::isActive(){
    return active;
}

void Laser::launch(glm::vec2 pos){
    active = true;
    ignoreCollisions = false;
    position = pos;
    hitbox->moveTo(position);
}

void Laser::update(float deltaTime){
    if(!active) return;
    position += velocity*deltaTime;
    if(position.y < 0){
        active = false;
        ignoreCollisions = true;
    }

    hitbox->moveTo(position);
}

void Laser::hit(PhysicsEntity* otherEntity){
    active = false;
    ignoreCollisions = true;
}
