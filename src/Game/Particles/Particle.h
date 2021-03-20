#ifndef PARTICLE_H
#define PARTICLE_H

#include <stdlib.h>

#include "../GameObject.h"

class Particle : public GameObject{
    private:
        float lifeTime;

    public:
        Particle() = default;
        Particle(glm::vec2 position,float rotation,glm::vec2 size,glm::vec3 color,glm::vec2 velocity,float lifeTime,Texture2D& sprite);

        void update(float deltaTime);

        void respawn(glm::vec2 pos,glm::vec2 vel,float life);

        bool isDead();
};

#endif