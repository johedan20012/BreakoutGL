#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

#include "BoxCollider.h"
#include "CircleCollider.h"
#include "../Game/GameObject.h"

#include "../IO/Keyboard.h"

class PhysicsObject : public GameObject{
    protected:
        //int id; Inservible por el momento
        Collider* hitbox; //Esto esta mal XD, pero shhh, permite el polimorfismo

    public:
        PhysicsObject() = default;
        PhysicsObject(glm::vec2 position,float rotation,glm::vec2 size,glm::vec3 color,glm::vec2 velocity,Texture2D& sprite,Collider* hitbox);
        ~PhysicsObject();

        Collider* getHitbox();

        bool checkCollisionWith(PhysicsObject& other);

        virtual void hit(PhysicsObject& other);
    protected:
        void updateHitbox(glm::vec2 position);

        glm::vec2 directionVector(glm::vec2 vector);
};

#endif 