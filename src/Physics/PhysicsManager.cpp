#include "PhysicsManager.h"

std::vector<PhysicsEntity*> PhysicsManager::entities;

int PhysicsManager::lastId = 0;

unsigned int PhysicsManager::registerEntity(PhysicsEntity* entity){
    entities.push_back(entity);
    
    return ++lastId;
}

void PhysicsManager::unregisterEntity(unsigned int id){
    for(unsigned int i = 0; i<entities.size(); i++){
        if(entities[i]->getId() == id){
            entities.erase(entities.begin()+i);
            break;
        }
    }

    if(entities.size() == 0) lastId = 0;
}

void PhysicsManager::update(){
    /*for(unsigned int i = 0; i<entities[1].size(); i++){
        std::cout<<(int)entities[1][i]->getType()<<"\n";
    }*/
    //Maneja las colisiones entre las entidades
    for (unsigned int k = 0; k < entities.size(); k++) {
        for (unsigned int l = k+1; l < entities.size(); l++) {
            if (entities[k]->checkCollision(entities[l])) {
                entities[k]->hit(entities[l]);
                entities[l]->hit(entities[k]);
            }
        }
    }
}

void PhysicsManager::cleanup(){
    entities.clear();
}