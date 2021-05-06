#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "Modifier.h"
#include "Laser.h"

#include "../Graphics/SpriteManager.h"

#include "../IO/Keyboard.h"
#include "../IO/Mouse.h"

#include "../Physics/PhysicsEntity.h"
#include "../Physics/PhysicsManager.h"

const glm::vec2 PLAYER_INITIAL_SIZE(100.0f,20.0f);

class Player : public GameObject, public PhysicsEntity{
    private:
        unsigned int lives;
        bool sticky;
        bool shootLasers;
        unsigned char sizeBar; //0 es el más pequeño, 1 es normal y 4 el más grande
        unsigned int score;

        float mouseOldPosX;

        static const int NUM_LASERS = 6;

        Laser lasers[NUM_LASERS];

    public:
        Player() = default;
        Player(Texture2D& sprite);
        ~Player();

        void init();

        void update(float deltaTime);

        void render(Shader& shader);

        void addScore(unsigned int points);
        unsigned int getScore();

        bool isSticky();
        bool hasLasers();

        void applyModifier(ModifierType modifier);

        void loseLive();
        unsigned int getLives();
        bool gameover();

        void hit(PhysicsEntity* otherEntity) override;

    private:
        void handleInput(float deltaTime);
};

#endif
