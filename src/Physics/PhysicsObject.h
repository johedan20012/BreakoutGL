#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

#include "BoxCollider.h"
#include "CircleCollider.h"
#include "../Game/GameObject.h"

class PhysicsObject : public GameObject{
    private:
        int id;
        Collider* hitbox; //Esto esta mal XD, pero shhh, permite el polimorfismo

    public:
        PhysicsObject() = default;
        PhysicsObject(glm::vec2 position,float rotation,glm::vec2 size,glm::vec3 color,glm::vec2 velocity,Texture2D& sprite,Collider* hitbox);
        ~PhysicsObject();

        bool checkCollisionWith(PhysicsObject& other);

        virtual void hit(PhysicsObject& other);
};

#endif 