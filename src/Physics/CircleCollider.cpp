#include "CircleCollider.h"

CircleCollider::CircleCollider(glm::vec2 position,float radius)
    :Collider(ColliderType::CIRCLE),center(position+glm::vec2(radius,radius)),radius(radius){
        debugSprite = SpriteManager::getSprite("DEBUG_1");
    }

glm::vec2 CircleCollider::calculateCenter(){
    return center;
}

glm::vec2 CircleCollider::calculateDimensions(){
    return glm::vec2(radius*2.0f);
}

void CircleCollider::moveTo(glm::vec2 newPosition){
    center = newPosition+glm::vec2(radius,radius);
}

void CircleCollider::changeDimensions(glm::vec2 newDimensions){
    radius = newDimensions.x / 2.0f;
}

void CircleCollider::render(Shader& shader){
    SpriteRenderer::drawSprite(debugSprite,shader,center-glm::vec2(radius,radius),glm::vec2(radius*2.0f,radius*2.0f),0,glm::vec4(1.0f));
}

