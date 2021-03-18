#include "SpriteManager.h"

std::map<std::string,Texture2D> SpriteManager::sprites; //Map vacio 

void SpriteManager::loadSprite(const char* filename,std::string name,bool flip){
    if(sprites.count(name) > 0) return; // El elemento ya estaba cargado
    //sprites.insert ( std::pair<const char*,Texture2D>(name,Texture2D()) );
    sprites[name].generate();
    sprites[name].loadFile(filename,flip);
}

Texture2D& SpriteManager::getSprite(std::string name){
    return sprites.at(name);
}

void SpriteManager::clearSprite(std::string name){
    //Hacer cleanup a la textura "id"
    if(sprites.count(name) <= 0) return; //La textura no estaba en el map
    sprites[name].cleanup();
    sprites.erase(name);
}

void SpriteManager::cleanup(){
    for(auto& pair: sprites){
        pair.second.cleanup();
    }
    sprites.clear();
}