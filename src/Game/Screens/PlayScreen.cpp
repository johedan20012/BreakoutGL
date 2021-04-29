#include "PlayScreen.h"

PlayScreen::PlayScreen(TextFont& fuente)
    :state(PlayState::PLAY),numLevel(1),level(),fuente(fuente),Screen(ScreenType::PLAY_SCREEN){}

void PlayScreen::init(){
    
    level.load("assets/levels/test.txt",800,300,fuente);

    background = SpriteManager::getSprite("background");
}

void PlayScreen::update(float deltaTime){
    if(state == PlayState::GAMEOVER) return;

    handleInput();

    if(state == PlayState::PLAY){
        level.update(deltaTime);

        if(level.isCompleted()){
            //Cambiar de nivel
            numLevel++;
            //DELETE THIS -> 
            state = PlayState::GAMEOVER;
            //FIXME
        }
    }
}

void PlayScreen::render(){
    Shader& shader = ShaderManager::getShader("shader");
    SpriteRenderer::drawSprite(background,shader,glm::vec2(0.0f,0.0f),glm::vec2(800.0f,600.0f),0,glm::vec4(1.0f));
    level.render(shader);
    if(state == PlayState::PAUSE){
        //Renderizar la pantalla de pausa
        //FIXME
    }else if(state == PlayState::GAMEOVER){
        //Renderizar la pantalla de gameover
        //FIXME
    }
}

bool PlayScreen::finished(){
    return (state == PlayState::GAMEOVER);
}

void PlayScreen::handleInput(){
    if(Keyboard::keyWentDown(GLFW_KEY_P)){
        if(state == PlayState::PLAY){
            state = PlayState::PAUSE;
        }else if(state == PlayState::PAUSE){
            state = PlayState::PLAY;
        }
    }
}