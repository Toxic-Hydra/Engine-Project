//
// Created by ivanl on 6/19/2020.
//

#ifndef ENGINE_GAME_H
#define ENGINE_GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <memory>

#include "AssetManager.h"
#include "Input.h"
#include "NetworkUtils.h"


class Game {
private:
    int ticksLastFrame;
    SDL_Window *window;
    bool isRunning;
    std::unique_ptr<TCPConnection> connectTCP;
    std::unique_ptr<UDPConnection> connectUDP;

public:
    Game();
    ~Game();
    //GLOBALS
    //Renderer static
    static SDL_Renderer *renderer;
    //static SDL_Event events;
    static Input *input;
    static AssetManager *assetManager;

    void Initialize(std::string windowName, int width, int height);
    bool Running();
    void LoadGame();
    void ProcessInput();
    void Update();
    void Render();
    void Destroy();
    



};


#endif //ENGINE_GAME_H
