#include "Keyboard.h"

bool Keyboard::keys[GLFW_KEY_LAST] = { 0 };
bool Keyboard::keysChanged[GLFW_KEY_LAST] = { 0 };

//Callback para el estado de la tecla
void Keyboard::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action != GLFW_RELEASE) {
		if (!keys[key]) {
			keys[key] = true;
		}
	} else {
		keys[key] = false;
	}

	keysChanged[key] = (action != GLFW_REPEAT);
}

//Funciones de acceso
bool Keyboard::key(int key) {
	return keys[key];
}
bool Keyboard::keyChanged(int key) {
	return keysChanged[key];
}
bool Keyboard::keyWentUp(int key) {
	return !keys[key] && keysChanged[key];
}
bool Keyboard::keyWentDown(int key) {
	return keys[key] && keysChanged[key];
}

void Keyboard::reset(){
	for(int i=0; i<GLFW_KEY_LAST; i++){
		keysChanged[i] = false;
	}
}