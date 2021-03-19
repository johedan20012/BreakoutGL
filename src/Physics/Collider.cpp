#include "Collider.h"

Collider::Collider(ColliderType type)
    :type(type){}

ColliderType Collider::getType(){
    return type;
}

void Collider::render(Shader& shader){
    
}

