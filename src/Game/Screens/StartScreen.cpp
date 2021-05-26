#include "StartScreen.h"

StartScreen::StartScreen(TextFont& fuente)
    :fuente(fuente),playInfinite(false),Screen(ScreenType::START_SCREEN){
        buttons[0] = Button("Modo normal",fuente,glm::vec2(290,300));
        buttons[1] = Button("Modo infinito",fuente,glm::vec2(290,350));
        buttons[2] = Button("Salir",fuente,glm::vec2(290,400));
    }

void StartScreen::init(){
    shader = ShaderManager::getShader("shader");

    nombre = SpriteManager::getSprite("INICIO_nombre");
}

void StartScreen::update(float deltaTime){
    for(int i = 0; i<NUM_BUTTONS; i++){
        buttons[i].update();
    }

    if(buttons[1].isActive() || buttons[0].isActive()){
        if(buttons[1].isActive()) playInfinite = true;
        state = ScreenState::FINISHED;
    }

    if(buttons[2].isActive()){
        state = ScreenState::CLOSE_GAME;
    }
}

void StartScreen::render(){
    SpriteRenderer::drawSprite(nombre,shader,glm::vec2(150.0f,150.0f),glm::vec2(500.0f,100.0f),0,glm::vec4(1.0f));

    Shader textShader = ShaderManager::getShader("textShader");
    for(int i =0 ; i<NUM_BUTTONS; i++){
        buttons[i].render(textShader);
    }
}

bool StartScreen::gameInfinite(){
    return playInfinite;
}