#ifndef MODIFIER_H
#define MODIFIER_H

#include "GameObject.h"
#include "../Physics/PhysicsEntity.h"
#include "../Physics/PhysicsManager.h"

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

class Modifier : public GameObject, public PhysicsEntity{
    private:
        ModifierType modType;
        bool active;
        bool applyEffect;

    public:
        Modifier(glm::vec2 position,glm::vec2 velocity,ModifierType type,Texture2D& sprite);
        ~Modifier();

        ModifierType getModType();

        bool isActive();
        bool shouldApplyEffect();

        void update(float deltaTime);

        void hit(PhysicsEntity* otherEntity) override;
};

#endif