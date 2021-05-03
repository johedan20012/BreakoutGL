#include "PhysicsManager.h"

std::vector<PhysicsEntity*> PhysicsManager::entities[static_cast<unsigned long long>(CollisionLayers::MAX_LAYERS)];

int PhysicsManager::flags[static_cast<unsigned long long>(CollisionLayers::MAX_LAYERS)];

int PhysicsManager::lastId = 0;

void PhysicsManager::setLayerCollisionFlags(CollisionLayers layer,CollisionFlags flag){
    flags[static_cast<unsigned int>(layer)] = static_cast<unsigned int>(flag);
}

unsigned int PhysicsManager::registerEntity(PhysicsEntity* entity,CollisionLayers layer){
    entities[static_cast<unsigned int>(layer)].push_back(entity);
    
    return ++lastId;
}

void PhysicsManager::unregisterEntity(unsigned int id){
    for(unsigned int i = 0; i<static_cast<unsigned int>(CollisionLayers::MAX_LAYERS); i++){
        for(unsigned int j = entities[i].size()-1; j>=0; j--){
            if(entities[i][j]->getId() == id){
                entities[i].erase(entities[i].begin()+j);
            }
        }
    }
}

void PhysicsManager::update(){
    
    /*for(unsigned int i = 0; i<entities[1].size(); i++){
        std::cout<<(int)entities[1][i]->getType()<<"\n";
    }*/
    //Maneja las colisiones entre las capas de colision
    for(unsigned int i = 0; i<static_cast<unsigned int>(CollisionLayers::MAX_LAYERS); i++){
        for(unsigned int j = i; j<static_cast<unsigned int>(CollisionLayers::MAX_LAYERS); j++){
            if(flags[i] & (1<<j)){
                std::cout<<i<<" "<<j<<"\n";
                for (unsigned int k = 0; k < entities[i].size(); k++) {
					for (unsigned int l = 0; l < entities[j].size(); l++) {
						if (entities[i][k]->checkCollision(entities[j][l])) {
                            std::cout<<"--GG EZ";
                            entities[i][k]->hit(entities[j][l]);
							entities[j][l]->hit(entities[i][k]);
						}
					}
				}
            }
        }
    }
}

void PhysicsManager::cleanup(){
    for(unsigned int  i =0; i<static_cast<unsigned int>(CollisionLayers::MAX_LAYERS); i++){
        entities[i].clear();
    }
}