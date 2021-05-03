#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include <vector>

#include "PhysicsEntity.h"

enum class CollisionLayers{
    PLAYER = 0,
    BRICKS,
    PROYECTILES, //La pelota y los laseres
    PLAYER_OBJECTS, // La pelota y los poderes
    /////////////////////////////////////////////
    MAX_LAYERS
};

enum class CollisionFlags{
    NONE = 0x00,
    PLAYER = 0X01,
    BRICKS = 0X02,
    PROYECTILES = 0X04,
    PLAYER_OBJECTS = 0X08,
};

class PhysicsManager{
    public:
        static std::vector<PhysicsEntity*> entities[static_cast<unsigned long long>(CollisionLayers::MAX_LAYERS)];

        static int flags[static_cast<unsigned long long>(CollisionLayers::MAX_LAYERS)];

        static int lastId;
    public:

        static void setLayerCollisionFlags(CollisionLayers layer,CollisionFlags flag);

        static unsigned int registerEntity(PhysicsEntity* entity,CollisionLayers layer);
        static void unregisterEntity(unsigned int id);

        static void update();

        static void cleanup();

    private:
        PhysicsManager();
};

#endif
