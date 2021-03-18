#ifndef SPRITEMANAGER_H
#define SPRITEMANAGER_H

#include <map>

#include "Texture2D.h"

class SpriteManager{
    private:
        static std::map<const char*,Texture2D> textures;

    public:
        static void loadTexture(const char* filename,const char* id, bool flip = true);

        static void clearTexture(const char* id);

        static void cleanup();

    private:
        SpriteManager();
};

#endif
