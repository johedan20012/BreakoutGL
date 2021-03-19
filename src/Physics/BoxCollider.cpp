#include "BoxCollider.h"

BoxCollider::BoxCollider(glm::vec2 position,glm::vec2 size)
    :Collider(ColliderType::AABB),min(position),max(position+size){}

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

glm::vec2 BoxCollider::calculateCenter(){
    return (min + max) / 2.0f;
}

/*
bool BoxCollider::collisionWith(Collider& other){
    if(other.getType() == ColliderType::AABB){
        glm::vec2 rad = calculateDimensions() / 2.0f;
        glm::vec2 radOther = other.calculateDimensions() / 2.0f;

        glm::vec2 distance = abs(calculateCenter() - other.calculateCenter());

        if(distance.x > rad.x + radOther.x){
            //No se sobreponen en este eje
            return false;
        }
        if(distance.y > rad.y + radOther.y){
            //No se sobreponen en este eje
            return false;
        }

        //Hay sobreposición en los 2 ejes
		return true;
    }else if(other.getType() == ColliderType::SPHERE){
        
    }
} */

#ifdef MIDEBUG
    void BoxCollider::render(Shader& shader){
        SpriteRenderer::drawSprite(sprite,shader,min,max-min,0,glm::vec3(1.0f));
    }
#endif