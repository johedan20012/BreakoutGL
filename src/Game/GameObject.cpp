#include "GameObject.h"

GameObject::GameObject(glm::vec2 position,float rotation,glm::vec2 size,glm::vec4 color,glm::vec2 velocity,Texture2D& sprite)
    :position(position),rotation(rotation),size(size),color(color),velocity(velocity),sprite(sprite){}

glm::vec2 GameObject::getPosition(){
    return position;
}

glm::vec2 GameObject::getSize(){
    return size;
}

glm::vec2 GameObject::getVelocity(){
    return velocity;
}

void GameObject::render(Shader& shader){
    SpriteRenderer::drawSprite(sprite,shader,position,size,rotation,color);
}