#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include "Screen.h"

#include "../UI/Button.h"

#include "../../IO/Mouse.h"

#include "../../Graphics/SpriteManager.h"
#include "../../Graphics/ShaderManager.h"
#include "../../Graphics/SpriteRenderer.h"
#include "../../Graphics/TextFont.h"

class StartScreen : public Screen{
    private:
        Texture2D nombre;
        Shader shader;
        TextFont fuente;

        static int const NUM_BUTTONS = 3;
        Button buttons[NUM_BUTTONS];

        bool playInfinite;
    public:
        StartScreen(TextFont& fuente);

        void init() override;

        void update(float deltaTime) override;

        void render() override;

        bool gameInfinite();
};

#endif