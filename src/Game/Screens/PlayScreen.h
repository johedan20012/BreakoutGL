#ifndef PLAYSCREEN_H
#define PLAYSCREEN_H

#include "Screen.h"

#include "../Level.h"
#include "../Player.h"

#include "../UI/Button.h"

#include "../../Graphics/ShaderManager.h"
#include "../../Graphics/TextFont.h"

enum class PlayState{
    PLAY,
    PAUSE,
    GAMEOVER,
};

class PlayScreen : public Screen{
    PlayState playState;
    unsigned int numLevel;
    Level* level;

    bool infinite;

    Texture2D background;

    Texture2D pauseBackground;
    Button pauseButtons[2];

    // 0 = no cambiar la caputura del cursor, 1 = capturar el cursor, 2 = dejar de capturar el cursor
    int mouseState; 

    Player player;

    TextFont fuente;
    public:
        PlayScreen(TextFont& fuente,bool infinite = false);
        ~PlayScreen() override;

        //Metodos de la clase padre
        void init() override;
        
        void update(float deltaTime) override;

        void render() override;

        int getMouseState();

    private:
        void handleInput();

        void loadNextLevel();
};  

#endif