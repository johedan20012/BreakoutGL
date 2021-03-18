#include "GameObject.h"

GameObject::GameObject(glm::vec2 position,float rotation,glm::vec2 size,glm::vec3 color,glm::vec2 velocity,Texture2D sprite)
    :position(position),rotation(rotation),size(size),color(color),velocity(velocity),sprite(sprite){}

void GameObject::render(Shader& shader){
    SpriteRenderer::drawSprite(sprite,shader,position,size,rotation,color);
}

/*void GameObject::cleanup(){
    sprite.cleanup();
}*/

void GameObject::update(){}