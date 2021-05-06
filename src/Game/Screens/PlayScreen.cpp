#include "PlayScreen.h"

PlayScreen::PlayScreen(TextFont& fuente)
    :Screen(ScreenType::PLAY_SCREEN)
    ,state(PlayState::PLAY),numLevel(1),fuente(fuente),level(nullptr){}

PlayScreen::~PlayScreen(){
    if(level != nullptr) delete level;
    level = nullptr;
}

void PlayScreen::init(){
    
    //level.load("assets/levels/test.txt",800,300,fuente);
    player = Player(SpriteManager::getSprite("bar"));
    player.init();
    Level::setPlayer(&player);
    Brick::setPlayer(&player);

    //Intento de nivel aleatorio
    level = new Level();
    level->load(20,25,800,400,fuente);

    background = SpriteManager::getSprite("background");
}

void PlayScreen::update(float deltaTime){
    if(state == PlayState::GAMEOVER) return;

    handleInput();

    if(state == PlayState::PLAY){
        level->update(deltaTime);

        
        if(level->isCompleted()){
            //Cambiar de nivel
            numLevel++;
            delete level;
            level = new Level();
            level->load(20,25,800,400,fuente,false);
        }else if(player.gameover()){
            state = PlayState::GAMEOVER;
        }
    }
}

void PlayScreen::render(){
    Shader& shader = ShaderManager::getShader("shader");
    SpriteRenderer::drawSprite(background,shader,glm::vec2(0.0f,0.0f),glm::vec2(800.0f,600.0f),0,glm::vec4(1.0f));
    level->render(shader);

    //Renderizar los puntos y vidas del jugador
    std::stringstream ss,ss2; ss << player.getLives();
    fuente.renderText("Vidas: "+ss.str(),glm::vec2(5.0f,5.0f),1.0f,ShaderManager::getShader("textShader"));
    ss2<<player.getScore();
    fuente.renderText("Puntos: "+ss2.str(),glm::vec2(600.0f,5.0f),1.0f,ShaderManager::getShader("textShader")); //Si alguien ve esto no lo replique porfavor esta mal

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

    if(Keyboard::keyWentDown(GLFW_KEY_R) == GLFW_PRESS){
        delete level;
        level = new Level();
        level->load(20,25,800,400,fuente,false);
    }
}