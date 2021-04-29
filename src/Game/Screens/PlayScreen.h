#ifndef PLAYSCREEN_H
#define PLAYSCREEN_H

#include "Screen.h"

#include "../Level.h"

#include "../../Graphics/ShaderManager.h"
#include "../../Graphics/TextFont.h"

enum class PlayState{
    PLAY,
    PAUSE,
    GAMEOVER,
};

class PlayScreen : public Screen{
    PlayState state;
    unsigned int numLevel;
    Level level;

    Texture2D background;

    TextFont fuente;
    public:
        PlayScreen(TextFont& fuente);

        //Metodos de la clase padre
        void init() override;
        
        void update(float deltaTime) override;

        void render() override;

        bool finished() override;

    private:
        void handleInput();
};  

#endif