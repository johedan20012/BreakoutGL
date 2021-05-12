#ifndef BUTTON_H
#define BUTTON_H

#include "../../Graphics/TextFont.h"
#include "../../Graphics/ShaderManager.h"

#include "../../Physics/BoxCollider.h"

#include "../../IO/Mouse.h"

class Button{
    private:
        enum class ButtonState{
            NORMAL,
            CLICKED,
            RELEASED,
        };
        
        std::string text;
        TextFont font;
        BoxCollider clickArea;

        ButtonState state;

    public:
        Button() = default;
        Button(std::string text,TextFont font,glm::vec2 pos);

        void center(float scrWidth,float scrHeight);

        void update();
        void render(Shader& shader);

        bool isActive();
};

#endif