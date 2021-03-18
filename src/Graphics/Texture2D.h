#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <glad/glad.h>
#include <stb/stb_image.h>

class Texture2D{
    private:
        unsigned int textureId;
    public:
        Texture2D();

        void generate();

        void loadFile(const char* filename,bool flip = true);

        void bind();

        void cleanup();
};


#endif