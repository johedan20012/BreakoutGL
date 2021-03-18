#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

enum class GameState{
    ACTIVE,MENU,WIN
};

class Game{
    private:
        GameState state;

        int screenWidth,screenHeight;
    public:
        Game();

        void init();

        void update();

        void render();
};

#endif