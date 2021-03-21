#include "Particle.h"

Particle::Particle(glm::vec2 position,float rotation,glm::vec2 size,glm::vec4 color,glm::vec2 velocity,float lifeTime,Texture2D& sprite)
    :GameObject(position,rotation,size,color,velocity,sprite)
    ,lifeTime(lifeTime){}

void Particle::update(float deltaTime){
    position += velocity * deltaTime;

    color.w -= deltaTime * 2.5f;

    if(lifeTime>0.0f) lifeTime -= deltaTime;
}

void Particle::respawn(glm::vec2 pos,glm::vec2 vel,float life){
    float random = ((rand()%100)-50)/10.0f;
    float randomBright = 0.5f + ((rand() % 100) / 100.0f);

    position = pos+random+6.0f;
    velocity = vel*0.1f;
    lifeTime = life;
    color = glm::vec4(randomBright,randomBright,randomBright,1.0f);
}

bool Particle::isDead(){
    return (lifeTime <= 0.0f);
}