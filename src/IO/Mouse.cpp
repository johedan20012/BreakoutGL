#include "Mouse.h"

double Mouse::x = 0;
double Mouse::y = 0;

double Mouse::lastX = 0;
double Mouse::lastY = 0;

double Mouse::dx = 0;
double Mouse::dy = 0;

double Mouse::scrollDX = 0;
double Mouse::scrollDY = 0;

bool Mouse::buttons[GLFW_MOUSE_BUTTON_LAST] = { 0 };
bool Mouse::buttonsChanged[GLFW_MOUSE_BUTTON_LAST] = { 0 };

void Mouse::cursorPosCallback(GLFWwindow* window, double _x, double _y) {
	dx = _x - lastX;
	dy = lastY - _y; //Este eje esta invertido
	lastX = x;
	lastY = y;

    x = _x;
	y = _y;
}

void Mouse::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	if (action != GLFW_RELEASE) {
		if (!buttons[button]) {
			buttons[button] = true;
		}
	} else {
		buttons[button] = false;
	}

	buttonsChanged[button] = (action != GLFW_REPEAT);
}

void Mouse::mouseWheelCallback(GLFWwindow* window, double dx, double dy) {
	scrollDX = dx;
	scrollDY = dy;
}

double Mouse::getMouseX() {
	return x;
}

double Mouse::getMouseY() {
	return y;
}

double Mouse::getDX() {
	return dx;
}

double Mouse::getDY() {
	return dy;
}

double Mouse::getScrollDX() {
	return scrollDX;
}

double Mouse::getScrollDY() {
	return scrollDY;
}

bool Mouse::button(int button) {
	return buttons[button];
}

bool Mouse::buttonChanged(int button) {
	return buttonsChanged[button];
}

bool Mouse::buttonWentUp(int button) {
	return !buttons[button] && buttonsChanged[button];
} 

bool Mouse::buttonWentDown(int button) {
	return buttons[button] && buttonsChanged[button];
}

void Mouse::reset(){
	for(unsigned int i=0; i<GLFW_MOUSE_BUTTON_LAST; i++){
		buttonsChanged[i] = false;
	}
}