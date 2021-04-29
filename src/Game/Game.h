#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <glad/glad.h> //Maneja las direcciones de las funciones de OpenGl, siempre incluir antes de GLFW
#include <GLFW/glfw3.h> //Maneja la creación de ventana , i/0, etc.

// Libreria para matematicas
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <stdlib.h>
#include <time.h>       

#include "Screens/PlayScreen.h"
#include "Screens/StartScreen.h"

#include "../IO/Mouse.h"
#include "../IO/Keyboard.h"

#include "../Graphics/ShaderManager.h"
#include "../Graphics/SpriteManager.h"
#include "../Graphics/TextFont.h"

class Game{
    private:
        static int screenWidth,screenHeight;

        float deltaTime  = 0.0f;
        float lastFrame = 0.0f;

        TextFont fuente;

        Screen* screen = nullptr;

        GLFWwindow* window = nullptr;
    public:
        Game() = default;

        int init();

        void run();

        void cleanup();
    private:
        static void framebufferSizeCallback(GLFWwindow* window,int witdh, int height);
};

#endif