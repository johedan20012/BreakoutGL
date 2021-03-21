#include "ParticleGenerator.h"

ParticleGenerator::ParticleGenerator(glm::vec2 sizeParticle,int noParticles,Texture2D& sprite)
    :noParticles(noParticles),sprite(sprite){
    for(int i=0; i<noParticles; i++){
        particles.push_back(Particle(glm::vec2(0.0f),0,sizeParticle,glm::vec4(1.0f),glm::vec2(0.0f),0.0f,sprite));
    }
}

void ParticleGenerator::update(GameObject& object,float deltaTime){
    bool particleSpawned = false;
    for(int i=0; i<particles.size(); i++){
        if(particles[i].isDead() && !particleSpawned){ //Spawnea una nueva particula si es posible
            particles[i].respawn(object.getPosition(),object.getVelocity(),1.0f);
            particles[i].update(deltaTime);
            particleSpawned = true;
        }else{
            particles[i].update(deltaTime);
        }
    }
}

void ParticleGenerator::render(Shader& shader){
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    for(int i=0; i<particles.size(); i++){
        if(!particles[i].isDead()){
            particles[i].render(shader);
        }
    }
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
