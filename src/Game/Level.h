#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <string>
#include <sstream>
#include <stdlib.h> 

#include "Brick.h"
#include "Player.h"
#include "Ball.h"
#include "Laser.h"
#include "Modifier.h"
#include "Particles/ParticleGenerator.h"
#include "../Graphics/SpriteManager.h"
#include "../Physics/PhysicsFunctions.h"

class Level{
    private:
        std::vector<Brick> bricks;
        int noBricks;
        Player player;

        static const int NUM_LASERS = 6;

        Laser lasers[NUM_LASERS];

        Ball ball;

        Modifier powerUp;

        ParticleGenerator ballParticles;

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