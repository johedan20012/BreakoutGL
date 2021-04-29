#include "StartScreen.h"

StartScreen::StartScreen(TextFont& fuente)
    :fuente(fuente),finish(false),Screen(ScreenType::START_SCREEN){}

void StartScreen::init(){
    shader = ShaderManager::getShader("shader");

    nombre = SpriteManager::getSprite("INICIO_nombre");
    fondo = SpriteManager::getSprite("background");
}

void StartScreen::update(float deltaTime){
    if(Mouse::buttonWentDown(GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
        finish = true;
    }
}

void StartScreen::render(){
    SpriteRenderer::drawSprite(fondo,shader,glm::vec2(0.0f,0.0f),glm::vec2(800.0f,600.0f),0,glm::vec4(1.0f));
    SpriteRenderer::drawSprite(nombre,shader,glm::vec2(150.0f,200.0f),glm::vec2(500.0f,100.0f),0,glm::vec4(1.0f));

    fuente.renderText("Haz click para empezar",glm::vec2(220.0f,350.0f),1.0f,ShaderManager::getShader("textShader"));
}

bool StartScreen::finished(){
    return finish;
}