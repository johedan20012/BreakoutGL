#include "PhysicsEntity.h"

PhysicsEntity::PhysicsEntity(Collider* hitbox,EntityType type,CollisionLayers collisionLayer)
    :hitbox(hitbox),type(type),ignoreCollisions(false){

}

Collider* PhysicsEntity::getHitbox(){
    return hitbox;
}

EntityType PhysicsEntity::getType(){
    return type;
}

unsigned int PhysicsEntity::getId(){
    return id;
}

void PhysicsEntity::setIgnoreCollisions(bool flag){
    ignoreCollisions = flag;
}

bool PhysicsEntity::checkCollision(PhysicsEntity* otherEntity){
    if(ignoreCollisions || otherEntity->ignoreCollisions) return false;

    if(hitbox->getType() == ColliderType::AABB && otherEntity->hitbox->getType() == ColliderType::AABB){
        return Physics::BoxBoxCollision(*(static_cast<BoxCollider*>(hitbox)),*(static_cast<BoxCollider*>(otherEntity->hitbox)));
    }else if(hitbox->getType() == ColliderType::AABB){ //otherEntity tiene hitbox de tipo Circle
        return Physics::BoxCircleCollision(*(static_cast<BoxCollider*>(hitbox)),*(static_cast<CircleCollider*>(otherEntity->hitbox)));
    }else if(otherEntity->hitbox->getType() == ColliderType::AABB){ // this tiene hitbox de tipo Circle
        return otherEntity->checkCollision(this);
    }
    //this y otherEntity tienen hitbox de tipo Circle
    return Physics::CircleCircleCollision(*(static_cast<CircleCollider*>(hitbox)),*(static_cast<CircleCollider*>(otherEntity->hitbox)));
}