#include "Brick.h"

Brick::Brick(glm::vec2 position,glm::vec2 size,glm::vec3 color,Texture2D sprite,bool isSolid)
    : GameObject(position,0,size,color,glm::vec2(0.0f,0.0f),sprite)
    , isSolid(isSolid),destroyed(false){
    hitbox = BoxCollider(position,size);
}

BoxCollider& Brick::getHitbox(){
    return hitbox;
}

bool Brick::isDestroyed(){
    return destroyed;
}

void Brick::hit(){
    if(isSolid) return;
    destroyed = true;
}