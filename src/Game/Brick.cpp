#include "Brick.h"

#include "Level.h"
#include "Ball.h"

Player* Brick::player = nullptr;
Level* Brick::level = nullptr;

Brick::Brick(glm::vec2 position,glm::vec2 cellPos,glm::vec2 size,glm::vec4 color,Texture2D sprite,bool isSolid)
    : GameObject(position,0,size,color,glm::vec2(0.0f,0.0f),sprite)
    , PhysicsEntity(new BoxCollider(position,size),EntityType::BRICK,(unsigned int)(EntityType::BALL | EntityType::LASER))
    , cellPos(cellPos),isSolid(isSolid),destroyed(false){
        id = PhysicsManager::registerEntity(this);
        collisionTypes = (unsigned int)(EntityType::BALL | EntityType::LASER);
}

Brick::~Brick(){
    PhysicsManager::unregisterEntity(id);
}

bool Brick::isDestroyed(){
    return destroyed;
}

glm::vec2 Brick::getCellPos(){
    return cellPos;
}

void Brick::hit(PhysicsEntity* otherEntity){
    if(isSolid) return;

    if(otherEntity->getType() == EntityType::BALL){
        if(rand()%2){
            level->spawnModifier(position);
        }
        player->addScore(20);
        if(static_cast<Ball*>(otherEntity)->hasFire()){
            level->setExplosion(cellPos);
        }
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

void Brick::setLevel(Level* l){
    level = l;
}