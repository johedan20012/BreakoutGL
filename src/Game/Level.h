#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <string>
#include <sstream>

#include "Brick.h"

class Level{
    private:
        std::vector<Brick> bricks;
        
    public:
        Level();

        void load(const char* file,unsigned int levelWidth,unsigned int levelHeight,Texture2D& brick,Texture2D& solidBrick);

        void update();

        void render(Shader& shader);

        bool isCompleted();
    
    private:
        void init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth,unsigned int levelHeight,Texture2D& brick,Texture2D& solidBrick);
};

#endif