#include "Particle.h"

Particle::Particle(glm::vec2 position,float rotation,glm::vec2 size,glm::vec4 color,glm::vec2 velocity,float lifeTime,Texture2D& sprite)
    :GameObject(position,rotation,size,color,velocity,sprite)
    ,lifeTime(lifeTime){}

void Particle::update(float deltaTime){
    position += velocity * deltaTime;

    color.w -= deltaTime * 2.5f;

    if(lifeTime>0.0f) lifeTime -= deltaTime;
}

void Particle::respawn(glm::vec2 pos,glm::vec2 vel,float life,glm::vec4 col){
    position = pos;
    velocity = vel;
    lifeTime = life;
    color = col;
}

bool Particle::isDead(){
    return (lifeTime <= 0.0f);
}