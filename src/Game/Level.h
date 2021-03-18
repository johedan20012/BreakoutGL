#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <string>
#include <sstream>

#include "Brick.h"
#include "Player.h"
#include "../Graphics/SpriteManager.h"

class Level{
    private:
        std::vector<Brick> bricks;
        
        Player player;

    public:
        Level();

        void load(const char* file,unsigned int levelWidth,unsigned int levelHeight);

        void update(float deltaTime);

        void render(Shader& shader);

        bool isCompleted();
    
    private:
        void init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth,unsigned int levelHeight);
};

#endif