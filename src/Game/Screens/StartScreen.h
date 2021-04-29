#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include "Screen.h"
#include "../../IO/Mouse.h"
#include "../../Graphics/SpriteManager.h"
#include "../../Graphics/ShaderManager.h"
#include "../../Graphics/SpriteRenderer.h"
#include "../../Graphics/TextFont.h"

class StartScreen : public Screen{
    private:
        Texture2D nombre,fondo;
        bool finish;
        Shader shader;
        TextFont fuente;

    public:
        StartScreen(TextFont& fuente);

        void init() override;

        void update(float deltaTime) override;

        void render() override;

        bool finished() override;
};

#endif