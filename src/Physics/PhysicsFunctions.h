#ifndef PHYSICSFUNCTIONS_HPP
#define PHYSICSFUNCTIONS_HPP

#include "BoxCollider.h"
#include "CircleCollider.h"

namespace Physics{
    bool BoxBoxCollision(BoxCollider& box,BoxCollider& box2);
    bool BoxCircleCollision(BoxCollider box,CircleCollider circle);
    bool CircleCircleCollision(CircleCollider circle,CircleCollider circle2);

    glm::vec2 DirectionVector(glm::vec2 vector);
}



#endif