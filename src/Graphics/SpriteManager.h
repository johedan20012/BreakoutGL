#ifndef SPRITEMANAGER_H
#define SPRITEMANAGER_H

#include <map>

#include "Texture2D.h"

class SpriteManager{
    private:
        static std::map<std::string,Texture2D> sprites;

    public:
        static void loadSprite(const char* filename,std::string name, bool flip = true);

        static Texture2D& getSprite(std::string name);

        static void clearSprite(std::string name);

        static void cleanup();

    private:
        SpriteManager();
};

#endif
