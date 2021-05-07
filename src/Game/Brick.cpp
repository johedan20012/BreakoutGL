#include "Brick.h"

#include "Ball.h"

Player* Brick::player = nullptr;

Brick::Brick(glm::vec2 position,glm::vec2 size,glm::vec4 color,Texture2D sprite,bool isSolid)
    : GameObject(position,0,size,color,glm::vec2(0.0f,0.0f),sprite)
    , PhysicsEntity(new BoxCollider(position,size),EntityType::BRICK,(unsigned int)(EntityType::BALL | EntityType::LASER))
    , isSolid(isSolid),destroyed(false),spawnModifier(false),explode(false){
        id = PhysicsManager::registerEntity(this);
        collisionTypes = (unsigned int)(EntityType::BALL | EntityType::LASER);
}

Brick::~Brick(){
    PhysicsManager::unregisterEntity(id);
}

void Brick::destroy(){
    if(isSolid) return;
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

void Brick::hit(PhysicsEntity* otherEntity){
    if(isSolid) return;

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