#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <string>
#include <sstream>
#include <stdlib.h> 

#include "Brick.h"
#include "Player.h"
#include "Ball.h"
#include "Modifier.h"
#include "../Graphics/SpriteManager.h"
#include "../Physics/PhysicsFunctions.h"

class Level{
    private:
        std::vector<Brick> bricks;
        
        Player player;

        Ball ball;

        Modifier powerUp;

    public:
        Level();

        void load(const char* file,unsigned int levelWidth,unsigned int levelHeight);

        void update(float deltaTime);

        void render(Shader& shader);

        bool isCompleted();
    
    private:
        void handleInput();

        void handleCollisions();

        void init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth,unsigned int levelHeight);
};

#endif