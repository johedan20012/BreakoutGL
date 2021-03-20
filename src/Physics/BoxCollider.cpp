#include "BoxCollider.h"

BoxCollider::BoxCollider(glm::vec2 position,glm::vec2 size)
    :Collider(ColliderType::AABB),min(position),max(position+size){
        debugSprite = SpriteManager::getSprite("DEBUG_2");
    }

glm::vec2 BoxCollider::getMin(){
    return min;
}

glm::vec2 BoxCollider::getMax(){
    return max;
}

glm::vec2 BoxCollider::calculateDimensions(){
    return max - min;
}

void BoxCollider::moveTo(glm::vec2 newPosition){
    max = newPosition + calculateDimensions();
    min = newPosition;
}

void BoxCollider::changeDimensions(glm::vec2 newDimensions){
    max = min + newDimensions;
}

glm::vec2 BoxCollider::calculateCenter(){
    return (min + max) / 2.0f;
}

void BoxCollider::render(Shader& shader){
    SpriteRenderer::drawSprite(debugSprite,shader,min,max-min,0,glm::vec3(1.0f));
}