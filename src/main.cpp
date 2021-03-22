#include "Game/Game.h"

Game game;

int main(){
    if(game.init() != 0){
        return -1;
    }

    game.run();

    game.cleanup();
}