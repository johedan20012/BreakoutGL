#ifndef PARTICLEGENERATOR_H
#define PARTICLEGENERATOR_H

#include <vector>

#include "Particle.h"

class ParticleGenerator{
    private:
        int noParticles;
        std::vector<Particle> particles;
        Texture2D sprite;

    public:
        ParticleGenerator() = default;
        ParticleGenerator(glm::vec2 sizeParticle,int noParticles,Texture2D& sprite);

        void update(GameObject& object,float deltaTime);

        void render(Shader& shader);
};

#endif