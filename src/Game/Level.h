#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <string>
#include <sstream>
#include <stdlib.h> 
#include <time.h>

#include <glm/gtc/noise.hpp>

#include <FastNoiseLite/FastNoiseLite.h>

#include "Brick.h"
#include "Player.h"
#include "Ball.h"
#include "Modifier.h"

#include "../Math/MathHelper.hpp"

#include "../Physics/PhysicsFunctions.h"
#include "../Physics/PhysicsManager.h"

#include "../Graphics/ShaderManager.h"
#include "../Graphics/SpriteManager.h"
#include "../Graphics/TextFont.h"

class Level{
    private:
        std::vector<Brick*> bricks;
        int noBricks;

        std::vector<Ball*> balls;

        std::vector<glm::vec2> explosions;

        Modifier* powerUp;

        TextFont fuente;

        static Player* player;
    public:
        Level() = default;
        ~Level();

        void load(const char* file,unsigned int levelWidth,unsigned int levelHeight,TextFont& fuente);

        void load(unsigned int noRows,unsigned int noColumns,unsigned int levelWidth,unsigned int levelHeight,TextFont& fuente,bool noise=true);

        void update(float deltaTime);

        void render(Shader& shader);

        bool isCompleted();

        //Metodos para que llamen los objetos del juego
        void setExplosion(glm::vec2 cellPos);

        void spawnModifier(glm::vec2 pos);

        void applyModifier(ModifierType modType);
    
    private:
        void handleInput();

        void init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth,unsigned int levelHeight);
    
        void spawnBall();
    //Metodos estaticos
    public:
        static void setPlayer(Player* p);
};

#endif