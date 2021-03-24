#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "Modifier.h"
#include "../Graphics/SpriteManager.h"
#include "../IO/Keyboard.h"
#include "../Physics/BoxCollider.h"

const glm::vec2 PLAYER_INITIAL_SIZE(100.0f,20.0f);

class Player : public GameObject{
    private:
        unsigned int lives;
        bool sticky;
        bool lasers;
        unsigned char sizeBar; //0 es el más pequeño, 1 es normal y 4 el más grande
        unsigned int score;
        BoxCollider hitbox;

    public:
        Player() = default;
        Player(Texture2D& sprite);

        BoxCollider& getHitbox();

        void update(float deltaTime);

        void addScore(unsigned int points);
        unsigned int getScore();

        bool isSticky();
        bool hasLasers();

        void applyModifier(ModifierType modifier);

    private:
        void handleInput(float deltaTime);
};

#endif
