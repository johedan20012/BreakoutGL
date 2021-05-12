#ifndef TEXTFONT_H
#define TEXTFONT_H

#include <map>

#include "GlMemory.hpp"
#include "Texture2D.h"
#include "Shader.h"

#include <ft2build.h>
#include FT_FREETYPE_H

struct Character{
    Texture2D texture;
    glm::ivec2 size;
    glm::ivec2 bearing;
    long int advance; //offset horizontal para avanzar al siguiente caracter
};

class TextFont{
    private:
        std::map<char, Character> characters;

        ArrayObject VAO;
    public:
        TextFont() = default;

        void init();

        void loadFont(std::string font,unsigned int fontSize);

        void renderText(std::string text,glm::vec2 pos,float scale,Shader shader,glm::vec4 color = glm::vec4(1.0f));

        glm::vec2 getTextDimensions(std::string text,float scale);

        void cleanup();

    private:
        void cleanCharacters();
};

#endif
