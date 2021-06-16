#include "PlayScreen.h"

PlayScreen::PlayScreen(TextFont& fuente,bool infinite)
    :infinite(infinite),Screen(ScreenType::PLAY_SCREEN)
    ,playState(PlayState::PLAY),numLevel(0),fuente(fuente),level(nullptr){}

PlayScreen::~PlayScreen(){
    if(level != nullptr) delete level;
    level = nullptr;
}

void PlayScreen::init(){
    player = Player(SpriteManager::getSprite("bar"));
    player.init();
    Level::setPlayer(&player);
    Brick::setPlayer(&player);

    loadNextLevel();
    pauseBackground = SpriteManager::getSprite("pauseBackground");

    pauseButtons[0] = Button("Reanudar",fuente,glm::vec2(200,300));
    pauseButtons[1] = Button("Salir a la pantalla principal",fuente,glm::vec2(200,350));
}

void PlayScreen::update(float deltaTime){
    if(playState == PlayState::GAMEOVER){
        if(Mouse::buttonWentDown(GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
            state = ScreenState::FINISHED;
        }
        return;
    }
    mouseState = 0;

    handleInput();

    if(playState == PlayState::PLAY){
        level->update(deltaTime);

        
        if(level->isCompleted()){
            //Cambiar de nivel
            delete level;
            loadNextLevel();
        }else if(player.gameover()){
            playState = PlayState::GAMEOVER;
        }
    }else{
        for(int i = 0; i<2; i++){
            pauseButtons[i].update();
        }

        if(pauseButtons[0].isActive()){
            playState = PlayState::PLAY;
            mouseState = 1;
        }

        if(pauseButtons[1].isActive()){
            state = ScreenState::FINISHED;
        }
    }
}

void PlayScreen::render(){
    Shader& shader = ShaderManager::getShader("shader");
    level->render(shader);

    //Renderizar los puntos y vidas del jugador
    std::stringstream ss,ss2; ss << player.getLives();
    Shader& textShader = ShaderManager::getShader("textShader");
    fuente.renderText("Vidas: "+ss.str(),glm::vec2(5.0f,5.0f),1.0f,textShader);
    ss2<<player.getScore();
    fuente.renderText("Puntos: "+ss2.str(),glm::vec2(600.0f,5.0f),1.0f,textShader); //Si alguien ve esto no lo replique porfavor esta mal

    if(playState == PlayState::PAUSE){
        //Renderizar la pantalla de pausa
        SpriteRenderer::drawSprite(pauseBackground,shader,glm::vec2(0.0f,0.0f),glm::vec2(800.0f,600.0f),0,glm::vec4(1.0f));
        fuente.renderText("Juego pausado",glm::vec2(250,200),1.5f,textShader);
        for(int i = 0; i<2; i++){
            pauseButtons[i].render(textShader);
        }
    }else if(playState == PlayState::GAMEOVER){
        //Renderizar la pantalla de gameover
        fuente.renderText("Juego terminado",glm::vec2(225,200),1.5f,textShader);
        fuente.renderText("Puntaje final: "+ss2.str(),glm::vec2(200.0f,300.0f),1.3f,textShader);
        fuente.renderText("Haz click para finalizar",glm::vec2(230.0f,400.0f),1.0f,textShader);
    }
}

int PlayScreen::getMouseState(){
    return mouseState;
}

void PlayScreen::handleInput(){
    if(Keyboard::keyWentDown(GLFW_KEY_ESCAPE)){
        if(playState == PlayState::PLAY){
            playState = PlayState::PAUSE;
            mouseState = 2;
        }
    }
}

void PlayScreen::loadNextLevel(){
    numLevel++;
    level = new Level();
    if(infinite){
        level->load(20,20,800,400,fuente,true);
    }else{
        if(numLevel > 13){
            playState = PlayState::GAMEOVER;
            return;
        }
        std::stringstream ss;
        ss<<numLevel;
        std::string levelPath = "assets/levels/level"+ss.str()+".txt";
        level->load(levelPath,800,400,fuente);
    }
}