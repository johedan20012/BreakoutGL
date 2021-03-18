#include "PhysicsObject.h"

PhysicsObject::PhysicsObject(glm::vec2 position,float rotation,glm::vec2 size,glm::vec3 color,glm::vec2 velocity,Texture2D& sprite,Collider* hitbox)
    :GameObject(position,rotation,size,color,velocity,sprite),hitbox(hitbox),id(0){}

PhysicsObject::~PhysicsObject(){
    delete hitbox;
    hitbox = nullptr;
}

bool PhysicsObject::checkCollisionWith(PhysicsObject& other){
    if(hitbox->getType() == ColliderType::AABB && other.hitbox->getType() == ColliderType::AABB){
        glm::vec2 rad = hitbox->calculateDimensions() / 2.0f;
        glm::vec2 radOther = other.hitbox->calculateDimensions() / 2.0f;

        glm::vec2 distance = abs(hitbox->calculateCenter() - other.hitbox->calculateCenter());

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
    }else if(hitbox->getType() == ColliderType::CIRCLE && other.hitbox->getType() == ColliderType::CIRCLE){
        glm::vec2 center = hitbox->calculateCenter();
        glm::vec2 centerOther = other.hitbox->calculateCenter();

        float radius = hitbox->calculateDimensions().x / 2.0f;
        float radiusOther = other.hitbox->calculateDimensions().x /2.0f;
        return (glm::length(center-centerOther) < radius + radiusOther);
    }else if(hitbox->getType() == ColliderType::CIRCLE){ //other tiene collider de tipo caja
        glm::vec2 center = hitbox->calculateCenter();

        glm::vec2 minOther = static_cast<BoxCollider*>(this->hitbox)->getMin();
        glm::vec2 maxOther = static_cast<BoxCollider*>(this->hitbox)->getMax();

        float radius = hitbox->calculateDimensions().x / 2.0f;

        float distSquared = 0.0f;
        float closestPoint = std::max(minOther.x,std::min(center.x,maxOther.x));
        distSquared += (closestPoint - center.x) * (closestPoint - center.x);
    
        closestPoint = std::max(minOther.y,std::min(center.y,maxOther.y));
        distSquared += (closestPoint - center.y) * (closestPoint - center.y);
    
        return distSquared < (radius * radius);
    }else{ //El objeto actual tiene collider de tipo caja y el otro de tipo esfera
        return other.checkCollisionWith(*this);
    }
}

void PhysicsObject::hit(PhysicsObject& other){
    
}