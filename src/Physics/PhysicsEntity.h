#ifndef PHYSICSENTITY_H
#define PHYSICSENTITY_H

#include "Collider.h"
#include "PhysicsFunctions.h"
#include "PhysicsManager.h"

enum class EntityType{
    PLAYER = 0,
    BALL,
    LASER,
    BRICK
};

class PhysicsEntity{
    private:
        unsigned int id;

        EntityType type;

    protected:
        Collider* hitbox;

        bool ignoreCollisions;
    
    public:
        PhysicsEntity() = default;
        PhysicsEntity(Collider* hitbox,EntityType type);
        ~PhysicsEntity();

        Collider* getHitbox();

        EntityType getType();

        unsigned int getId();

        void setIgnoreCollisions(bool flag);
        bool checkCollision(PhysicsEntity* otherEntity);

        virtual void hit(PhysicsEntity* otherEntity) = 0;
};

#endif

