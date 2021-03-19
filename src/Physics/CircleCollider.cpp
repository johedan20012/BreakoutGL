#include "CircleCollider.h"

CircleCollider::CircleCollider(glm::vec2 position,float radius)
    :Collider(ColliderType::CIRCLE),center(position+glm::vec2(radius,radius)),radius(radius){}

glm::vec2 CircleCollider::calculateCenter(){
    return center;
}

glm::vec2 CircleCollider::calculateDimensions(){
    return glm::vec2(radius*2.0f);
}

void CircleCollider::moveTo(glm::vec2 newPosition){
    center = newPosition;
}
