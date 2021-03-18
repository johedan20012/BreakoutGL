#ifndef COLLIDER_H
#define COLLIDER_H

#include <glm/glm.hpp>

enum class ColliderType{
    AABB, //Axis Aligned Boundign Box
    CIRCLE
};

class Collider{
    protected:
        ColliderType type;

    public:
        Collider(ColliderType type = ColliderType::AABB);

        ColliderType getType();

        virtual glm::vec2 calculateCenter() = 0;
        virtual glm::vec2 calculateDimensions() = 0;

        //virtual bool collisionWith(Collider& other);
};
#endif