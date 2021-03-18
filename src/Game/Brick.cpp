#include "Brick.h"

Brick::Brick(glm::vec2 position,glm::vec2 size,glm::vec3 color,Texture2D sprite,bool isSolid)
    : GameObject(position,0,size,color,sprite), isSolid(isSolid){}
