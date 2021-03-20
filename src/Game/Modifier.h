#ifndef MODIFIER_H
#define MODIFIER_H

#include "GameObject.h"
#include "../Physics/BoxCollider.h"

enum class ModifierType{
    LARGE_BAR = 0,
    SHORT_BAR,
    STICKY_BAR,
    LASER_BAR,
    RESET_BAR,
    FAST_BALL,
    SLOW_BALL,
    THROUGH_BALL,
    FIRE_BALL,
    EXTRA_BALL,
    REMOVE_BALL,
    CRAZY_TIME,
    EXTRA_LIFE,
    NEXT_LEVEL,
    //=========================
    NUM_TYPES
};

class Modifier : public GameObject{
    private:
        BoxCollider hitbox;
        ModifierType type;
        bool active;

    public:
        Modifier() = default;
        Modifier(glm::vec2 position,glm::vec2 velocity,ModifierType type,Texture2D& sprite);

        BoxCollider& getHitbox();

        ModifierType getType();

        bool isActive();

        void desactivate();

        void update(float deltaTime);
};

#endif