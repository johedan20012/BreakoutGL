#include "Brick.h"

Brick::Brick(glm::vec2 position,glm::vec2 size,glm::vec4 color,Texture2D sprite,bool isSolid)
    : GameObject(position,0,size,color,glm::vec2(0.0f,0.0f),sprite)
    , PhysicsEntity(new BoxCollider(position,size),EntityType::BRICK)
    , isSolid(isSolid),destroyed(false){}

bool Brick::isDestroyed(){
    return destroyed;
}

void Brick::hit(PhysicsEntity* otherEntity){
    if(isSolid) return;
    destroyed = true;
    ignoreCollisions = true;
}