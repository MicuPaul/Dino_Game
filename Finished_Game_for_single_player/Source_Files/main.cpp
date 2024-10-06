#include "stdafx.h"
#include "Game.h"

int main(){

    srand(static_cast<unsigned>(time(0)));

    Game game;

    while(game.getWindow().isOpen()){
        game.update();
        game.render();
    }

    std::cout<<"Game Version: For single player";

    return 0;
}

