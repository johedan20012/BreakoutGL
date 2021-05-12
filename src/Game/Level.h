#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <string>
#include <sstream>
#include <stdlib.h> 
#include <time.h>

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
        std::vector<std::vector<Brick*>> bricks;
        int noBricks;
        bool finished;

        std::vector<Ball*> balls;

        Modifier* powerUp;

        TextFont fuente;

        static const int MOV[4][2];

        static Player* player;
        
    public:
        Level() = default;
        ~Level();

        void load(std::string file,unsigned int levelWidth,unsigned int levelHeight,TextFont& fuente);

        void load(unsigned int noRows,unsigned int noColumns,unsigned int levelWidth,unsigned int levelHeight,TextFont& fuente,bool noise=true);

        void update(float deltaTime);

        void render(Shader& shader);

        bool isCompleted();
    
    private:
        //Metodos para modificar el nivel
        //=======================================
        void spawnModifier(glm::vec2 pos);

        void applyModifier(ModifierType modType);

        void splitBalls();
        //=========================================

        void handleInput();

        void init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth,unsigned int levelHeight);
    
    //Metodos estaticos
    //===================================
    public:
        static void setPlayer(Player* p);
    //===================================
};

#endif