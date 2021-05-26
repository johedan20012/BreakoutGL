#ifndef TERRAIN_H
#define TERRAIN_H

#include <FastNoiseLite/FastNoiseLite.h>

#include "../Graphics/GlMemory.hpp"
#include "../Graphics/Shader.h"

class Terrain{
    private:
        ArrayObject VAO;

        unsigned int NOIndices;

    public:
        Terrain() = default;

        void generate(int NOColumns,int NORows);

        void render(Shader& shader);

        void cleanup();
};

#endif