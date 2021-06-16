#ifndef TERRAIN_H
#define TERRAIN_H

#include <FastNoiseLite/FastNoiseLite.h>

#include "../Graphics/GlMemory.hpp"
#include "../Graphics/Shader.h"

class Terrain{
    private:
        ArrayObject VAO;

        unsigned int NOIndices;

        int seed;

    public:
        Terrain() = default;

        void init();

        void generate(int NOColumns,int NORows,int offset);

        void render(Shader& shader);

        void cleanup();
};

#endif