#ifndef PHYSICSENTITY_H
#define PHYSICSENTITY_H

#include "Collider.h"
#include "PhysicsFunctions.h"

enum class EntityType{
    PLAYER = 0x01,
    BALL = 0x02,
    LASER = 0x04,
    BRICK = 0x08,
    MODIFIER = 0x10
};

inline EntityType operator | (EntityType t1,EntityType t2){
    return static_cast<EntityType>(static_cast<unsigned int>(t1) | static_cast<unsigned int>(t2));
}

class PhysicsEntity{

    protected:
        unsigned int id;

        EntityType type;

        unsigned int collisionTypes;

        Collider* hitbox;

        bool ignoreCollisions;
    
    public:
        PhysicsEntity() = default;
        PhysicsEntity(Collider* hitbox,EntityType type,unsigned int collisionTypes);
        ~PhysicsEntity();

        Collider* getHitbox();

        EntityType getType();

        unsigned int getId();

        void setIgnoreCollisions(bool flag);
        bool checkCollision(PhysicsEntity* otherEntity);

        virtual void hit(PhysicsEntity* otherEntity) = 0;
};

#endif

