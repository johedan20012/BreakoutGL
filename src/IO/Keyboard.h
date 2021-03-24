#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <GLFW/glfw3.h>

class Keyboard{
    public:
        //Callback para el estado de la tecla
		static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

		//Funciones de acceso
		static bool key(int key);
		static bool keyChanged(int key);
		static bool keyWentUp(int key);
		static bool keyWentDown(int key);

		static void reset();

    private:
        static bool keys[];
		static bool keysChanged[];

        Keyboard();
};

#endif