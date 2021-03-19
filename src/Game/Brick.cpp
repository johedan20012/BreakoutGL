#include "Brick.h"

Brick::Brick(glm::vec2 position,glm::vec2 size,glm::vec3 color,Texture2D sprite,bool isSolid)
    : PhysicsObject(position,0,size,color,glm::vec2(0.0f,0.0f),sprite,new BoxCollider(position,size)), isSolid(isSolid),destroyed(false){}

bool Brick::isDestroyed(){
    return destroyed;
}

void Brick::hit(PhysicsObject& other){
    if(isSolid) return;
    destroyed = true;
}