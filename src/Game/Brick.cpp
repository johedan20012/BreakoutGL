#include "Brick.h"

#include "Ball.h"

Player* Brick::player = nullptr;

Brick::Brick(glm::vec2 position,glm::vec2 size,int resistance,Texture2D sprite,bool isSolid)
    : GameObject(position,0,size,glm::vec4(1.0f),glm::vec2(0.0f,0.0f),sprite)
    , PhysicsEntity(new BoxCollider(position,size),EntityType::BRICK,(unsigned int)(EntityType::BALL | EntityType::LASER))
    , resistance(resistance),isSolid(isSolid),destroyed(false),spawnModifier(false),explode(false){
        if(!isSolid)updateColor();
        id = PhysicsManager::registerEntity(this);
        collisionTypes = (unsigned int)(EntityType::BALL | EntityType::LASER);
}

Brick::~Brick(){
    PhysicsManager::unregisterEntity(id);
}

void Brick::destroy(){
    if(isSolid) return;
    resistance--;
    updateColor();
    if(resistance > 0) return;

    player->addScore(10);
    destroyed = true;
    ignoreCollisions = true;
}

bool Brick::isDestroyed(){
    return destroyed;
}

bool Brick::shouldSpawnModifier(){
    return spawnModifier;
}

bool Brick::shouldExplode(){
    return explode;
}

void Brick::updateColor(){
    switch(resistance){
        case 4: //Morado
            color = glm::vec4(0.5f,0.18f,0.58f,1.0f); 
            break;
        case 3: //Naranja
            color = glm::vec4(0.98f,0.5f,0.14f,1.0f); 
            break;
        case 2: //Verde
            color = glm::vec4(0.04f,0.7f,0.3f,1.0f); 
            break;
        case 1: //Azul
            color = glm::vec4(0.02f,0.2f,0.9f,1.0f); 
            break;
        case 0:
            color = glm::vec4(0.0f);
            break;
    }
}

void Brick::hit(PhysicsEntity* otherEntity){
    if(isSolid) return;
    resistance--;
    updateColor();
    if(resistance > 0) return;

    if(otherEntity->getType() == EntityType::BALL){
        if(rand()%2){
            spawnModifier = true;
        }
        if(static_cast<Ball*>(otherEntity)->hasFire()){
            explode = true;
        }
        player->addScore(20);
    }else{ //Fui golpeado por un laser
        player->addScore(10);
    }
    destroyed = true;
    ignoreCollisions = true;
}

//Metodos estaticos
void Brick::setPlayer(Player* p){
    player = p;
}