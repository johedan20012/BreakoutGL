#include "Screen.h"

Screen::Screen(ScreenType type)
    :type(type),state(ScreenState::RUNNING){}

Screen::~Screen(){}

ScreenType Screen::getType(){
    return type;
}

ScreenState Screen::getState(){
    return state;
}