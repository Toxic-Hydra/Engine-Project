#include <iostream>
#include "Game.h"
#include "EngineConstants.h"
#include <memory>


int main(int argv, char** args) {

    std::shared_ptr<Game> game = std::make_shared<Game>();


    game->Initialize(std::string("Window"), WINDOW_WIDTH, WINDOW_HEIGHT);
    while(game->Running())
    {
        game->ProcessInput();
        game->Update();
        game->Render();
    }


    game->Destroy();

    return 0;
}
