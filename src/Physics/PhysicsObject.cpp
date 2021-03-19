#include "PhysicsObject.h"

PhysicsObject::PhysicsObject(glm::vec2 position,float rotation,glm::vec2 size,glm::vec3 color,glm::vec2 velocity,Texture2D& sprite,Collider* hitbox)
    :GameObject(position,rotation,size,color,velocity,sprite),hitbox(hitbox){}

PhysicsObject::~PhysicsObject(){
    //if(hitbox == nullptr) return;
    //delete hitbox;
    //hitbox = nullptr;
}

bool PhysicsObject::checkCollisionWith(PhysicsObject& other){
    if(hitbox->getType() == ColliderType::AABB && other.hitbox->getType() == ColliderType::AABB){
        glm::vec2 rad = hitbox->calculateDimensions() / 2.0f;
        glm::vec2 radOther = other.hitbox->calculateDimensions() / 2.0f;

        glm::vec2 distance = abs(hitbox->calculateCenter() - other.hitbox->calculateCenter());

        if(distance.x > rad.x + radOther.x){
            //No se sobreponen en este eje
            return false;
            //return std::make_tuple(false,glm::vec2(0.0f),glm::vec2(0.0f));
        }
        if(distance.y > rad.y + radOther.y){
            //No se sobreponen en este eje
            return false;
            //return std::make_tuple(false,glm::vec2(0.0f),glm::vec2(0.0f));
        }

        //Hay sobreposición en los 2 ejes
        return true;
        //return std::make_tuple(true,glm::vec2(0.0f),glm::vec2(0.0f));
    }else if(hitbox->getType() == ColliderType::CIRCLE && other.hitbox->getType() == ColliderType::CIRCLE){
        glm::vec2 center = hitbox->calculateCenter();
        glm::vec2 centerOther = other.hitbox->calculateCenter();

        float radius = hitbox->calculateDimensions().x / 2.0f;
        float radiusOther = other.hitbox->calculateDimensions().x /2.0f;
        return (glm::length(center-centerOther) < radius + radiusOther);
        /*if (glm::length(center-centerOther) < radius + radiusOther){
            return std::make_tuple(true,glm::vec2(0.0f),glm::vec2(0.0f));
        }
        return std::make_tuple(false,glm::vec2(0.0f),glm::vec2(0.0f));*/
    }else if(hitbox->getType() == ColliderType::CIRCLE){ //other tiene collider de tipo caja
        glm::vec2 center = hitbox->calculateCenter();

        glm::vec2 halfDimensionsOther = other.hitbox->calculateDimensions() / 2.0f;
        glm::vec2 centerOther = other.hitbox->calculateCenter();

        glm::vec2 difference = center - centerOther;
        glm::vec2 clamped = glm::clamp(difference, -halfDimensionsOther,halfDimensionsOther);
        glm::vec2 closest = centerOther + clamped;
        difference = closest - center;
        return (glm::length(difference) <= hitbox->calculateDimensions().x);
        /*if(glm::length(difference) <= hitbox->calculateDimensions().x){
            return std::make_tuple(true,directionVector(difference),difference);
        }
        return std::make_tuple(false,glm::vec2(0.0f),glm::vec2(0.0f));*/
    }else{ //El objeto actual tiene collider de tipo caja y el otro de tipo esfera
        return other.checkCollisionWith(*this);
    }
}

void PhysicsObject::hit(PhysicsObject& other){
    
}

Collider* PhysicsObject::getHitbox(){
    return hitbox;
}

void PhysicsObject::updateHitbox(glm::vec2 position){
    hitbox->moveTo(position);
}

glm::vec2 PhysicsObject::directionVector(glm::vec2 vector){
    glm::vec2 compass[] = {
        glm::vec2(0.0f, 1.0f),	// up
        glm::vec2(1.0f, 0.0f),	// right
        glm::vec2(0.0f, -1.0f),	// down
        glm::vec2(-1.0f, 0.0f)	// left
    };
    float max = 0.0f;
    unsigned int best_match = -1;
    for (unsigned int i = 0; i < 4; i++){
        float dot_product = glm::dot(glm::normalize(vector), compass[i]);
        if (dot_product > max)
        {
            max = dot_product;
            best_match = i;
        }
    }
    return compass[best_match];
}