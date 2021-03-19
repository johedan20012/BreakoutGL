#include "PhysicsFunctions.h"

bool Physics::BoxBoxCollision(BoxCollider& box,BoxCollider& box2){
    glm::vec2 rad = box.calculateDimensions() / 2.0f;
    glm::vec2 radOther = box2.calculateDimensions() / 2.0f;

    glm::vec2 distance = abs(box.calculateCenter() - box2.calculateCenter());

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
}

bool Physics::BoxCircleCollision(BoxCollider box,CircleCollider circle){
    glm::vec2 center = circle.calculateCenter();

    glm::vec2 halfDimensionsOther = box.calculateDimensions() / 2.0f;
    glm::vec2 centerOther = box.calculateCenter();

    glm::vec2 difference = center - centerOther;
    glm::vec2 clamped = glm::clamp(difference, -halfDimensionsOther,halfDimensionsOther);
    glm::vec2 closest = centerOther + clamped;
    difference = closest - center;
    return (glm::length(difference) <= (circle.calculateDimensions().x/2.0f));
}

bool Physics::CircleCircleCollision(CircleCollider circle,CircleCollider circle2){
    glm::vec2 center = circle.calculateCenter();
    glm::vec2 centerOther = circle2.calculateCenter();

    float radius = circle.calculateDimensions().x / 2.0f;
    float radiusOther = circle2.calculateDimensions().x /2.0f;
    return (glm::length(center-centerOther) < radius + radiusOther);
}

glm::vec2 Physics::DirectionVector(glm::vec2 vector){
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