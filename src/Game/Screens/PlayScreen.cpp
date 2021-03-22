#include "PlayScreen.h"

PlayScreen::PlayScreen()
    :state(PlayState::PLAY),numLevel(1),level(){}

void PlayScreen::init(){
    // =================== SHADERS =============================
    ShaderManager::loadShader("assets/shaders/2DObject.vs","assets/shaders/2DObject.fs","shader");

    //Poner los uniforms
    glm::mat4 projection = glm::ortho(0.0f,800.0f,600.0f,0.0f,-1.0f,1.0f);
    Shader& shader = ShaderManager::getShader("shader");
    shader.activate();
    shader.setInt("image",0);
    shader.setFloatMat4("projection",projection);
    
    level.load("assets/levels/test.txt",800,300);

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