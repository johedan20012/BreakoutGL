#include "Player.h"

Player::Player(Texture2D& sprite)
    : GameObject(glm::vec2(350.0f,580.0f),0,PLAYER_INITIAL_SIZE,glm::vec4(1.0f),glm::vec2(500.0f,0.0f),sprite)
    , PhysicsEntity(new BoxCollider(glm::vec2(350.0f,580.0f),glm::vec2(100.0f,20.0f)),EntityType::PLAYER,(unsigned int)(EntityType::BALL | EntityType::MODIFIER))
    , lives(3),sticky(false),shootLasers(false),sizeBar(1),score(0),mouseOldPosX(Mouse::getMouseX()){}

void Player::init(){
     id = PhysicsManager::registerEntity(this);

     for(int  i=0; i<NUM_LASERS; i++){
        lasers[i] = Laser(SpriteManager::getSprite("laser"));
        lasers[i].init();
    }
}

Player::~Player(){
    if(id != 0) PhysicsManager::unregisterEntity(id);
}

void Player::update(float deltaTime){
    //Manejar la entrada
    handleInput(deltaTime);

    for(int i =0; i<NUM_LASERS; i++){
        lasers[i].update(deltaTime);
    }

    hitbox->moveTo(position);
}

void Player::render(Shader& shader){
    for(int i =0; i<NUM_LASERS; i++){
        if(!lasers[i].isActive()) continue;
        lasers[i].render(shader);
    }

    GameObject::render(shader);
}

void Player::addScore(unsigned int points){
    score += points;
}

unsigned int Player::getScore(){
    return score;
}

bool Player::isSticky(){
    return sticky;
}

bool Player::hasLasers(){
    return shootLasers;
}

void Player::applyModifier(ModifierType modifier){
    switch (modifier)
    {
        case ModifierType::LARGE_BAR:
            sizeBar++;
            if(sizeBar > 4)sizeBar = 4;
            break;
        
        case ModifierType::SHORT_BAR:
            sizeBar = 0;
            break;

        case ModifierType::STICKY_BAR:
            sticky = true;
            break;

        case ModifierType::LASER_BAR:
            shootLasers = true;
            break;
        case ModifierType::RESET_BAR:
            sticky = false;
            shootLasers = false;
            sizeBar = 1;
    }

    //Actualizar la barra del jugador con los valores actuales
    if(sizeBar == 0){
        size = PLAYER_INITIAL_SIZE - glm::vec2(PLAYER_INITIAL_SIZE.x/2.0f,0.0f);
    }else{
        size = PLAYER_INITIAL_SIZE + glm::vec2((PLAYER_INITIAL_SIZE.x/2.0f)*(sizeBar-1),0.0f);
    }
    if(position.x+size.x > 800.0f){
        position.x = 800.0f-size.x;
    }

    if(sticky){
        sprite = SpriteManager::getSprite("barSticky");
    }else{
        sprite = SpriteManager::getSprite("bar");
    }

    hitbox->changeDimensions(size);
    hitbox->moveTo(position);
}

void Player::loseLive(){
    if(lives > 0) lives --;
}

unsigned int Player::getLives(){
    return lives;
}

bool Player::gameover(){
    return (lives == 0);
}

void Player::hit(PhysicsEntity* otherEntity){}

void Player::handleInput(float deltaTime){
    float mouseNewPosX = Mouse::getMouseX();

    position.x += mouseNewPosX - mouseOldPosX;
    mouseOldPosX = mouseNewPosX;

    if(position.x > 800.0f-size.x){
        position.x = 800.0f-size.x;
    }else if(position.x < 0.0f){
        position.x = 0.0f;
    }

    if(Mouse::buttonWentDown(GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && shootLasers){
        int laser1 = -1,laser2 = -1;
        for(int i=0; i<NUM_LASERS; i++){
            if(!lasers[i].isActive()){
                if(laser1 == -1){
                    laser1 = i;
                }else{
                    laser2 = i;
                    break;
                }
            }
        }
        if(laser2 != -1){
            lasers[laser1].launch(position+glm::vec2(0.0f,-15.0f));
            lasers[laser2].launch(position+glm::vec2(size.x-20.0f,0.0f));
        }
    }
}