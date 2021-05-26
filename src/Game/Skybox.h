#ifndef SKYBOX_H
#define SKYBOX_H

#include "../Graphics/GlMemory.hpp"
#include "../Graphics/Shader.h"

class Skybox{
    private:
        static ArrayObject VAO;

        static unsigned int cubemapTexture;

    public:
        static void load();

        static void render(Shader& shader);

        static void cleanup();

    private:
        Skybox();
};

#endif