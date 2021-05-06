#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include <vector>

#include "PhysicsEntity.h"

class PhysicsManager{
    public:
        static std::vector<PhysicsEntity*> entities;

        static int lastId;
    public:

        static unsigned int registerEntity(PhysicsEntity* entity);
        static void unregisterEntity(unsigned int id);

        static void update();

        static void cleanup();

    private:
        PhysicsManager();
};

#endif
