#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "../IO/Keyboard.h"
#include "../Physics/BoxCollider.h"

enum class PlayerModifier{
    LARGE_BAR,
    SHORT_BAR,
    STICKY_BAR,
    LASER_BAR,
    RESET_BAR,
    FAST_BALL,
    SLOW_BALL,
    EXTRA_BALL,
    REMOVE_BALL,
    CRAZY_TIME
};

class Player : public GameObject{
    private:
        unsigned int lives;
        bool isSticky;
        bool hasLasers;
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

        void applyModifier(PlayerModifier modifier);

    private:
        void handleInput(float deltaTime);
};

#endif
