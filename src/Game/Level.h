#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <string>
#include <sstream>
#include <stdlib.h> 
#include <time.h>

#include <glm/gtc/noise.hpp>

#include "Brick.h"
#include "Player.h"
#include "Ball.h"
#include "Laser.h"
#include "Modifier.h"
#include "Particles/ParticleGenerator.h"

#include "../Physics/PhysicsFunctions.h"

#include "../Graphics/ShaderManager.h"
#include "../Graphics/SpriteManager.h"
#include "../Graphics/TextFont.h"

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

        TextFont fuente;
    public:
        Level();

        void load(const char* file,unsigned int levelWidth,unsigned int levelHeight,TextFont& fuente);

        void load(unsigned int noRows,unsigned int noColumns,unsigned int levelWidth,unsigned int levelHeight,TextFont& fuente);

        void update(float deltaTime);

        void render(Shader& shader);

        bool isCompleted();
    
    private:
        void handleInput();

        void handleCollisions();

        void init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth,unsigned int levelHeight);
};

#endif