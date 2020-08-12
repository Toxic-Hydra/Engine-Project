//
// Created by ivanl on 6/19/2020.
//

#include "Game.h"
#include "AssetManager.h"
#include "EntityManager.h"
#include "MapManager.h"

#include "components/TransformComponent.h"
#include "components/SpriteComponent.h"
#include "components/PlayerControl.h"


#include <SDL.h>
#include <SDL_image.h>
#include <SDL_net.h>
#include <iostream>

//Initaliza Statics & Globals
SDL_Renderer* Game::renderer;

Input* Game::input;
AssetManager* Game::assetManager;
EntityManager manager;
std::unique_ptr<MapManager> map;



Game::Game()
{
    isRunning = false;
}



void Game::Initialize(std::string windowName, int width, int height)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "COULD NOT INITIALIZE SDL" << std::endl;
        return;
    }

    if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) //Returns a bitmask of currently initiated systems, so & against img_init_png to test for true
    {
        std::cerr << "COULD NOT INITIALIZE SDL_IMAGES" << std::endl;
        return;
    }

    
    if (SDLNet_Init() == -1)
    {
        std::cerr << "COULD NOT INIT SDL NET" << std::endl;
        return;
    }

    connectTCP = std::make_unique<TCPConnection>();
    connectTCP->InitServerTCP();
    connectTCP->InitClientTCP();
    connectTCP->ServerAcceptTCP();

    connectTCP->ServerSendTCP();

    const char message[] = "TCP MESSAGE ORIGIN CLIENT";
    connectTCP->ClientSendTCP(message);

    

    connectUDP = std::make_unique<UDPConnection>();
    connectUDP->InitServerUDP();
    connectUDP->InitClientUDP();
    connectUDP->SendUDP("UDP MESSAGE RECEIVED\n");

    window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_BORDERLESS);
    if(!window)
    {
        std::cerr << "COULD NOT CREATE WINDOW" << std::endl;
        return;
    }

    renderer = SDL_CreateRenderer(window,-1, 0);
    if(!renderer)
    {
        std::cerr << "COULD NOT CREATE RENDERER" << std::endl;
        return;
    }

    

    Game::assetManager = new AssetManager();
    //Game::manager = std::make_unique<EntityManager>();
    Game::input = new Input("w", "a", "s", "d");



    isRunning = true;
    LoadGame();

}



void Game::LoadGame()
{
    //Todo: Async loading for loading screen.
    assetManager->AddTexture("dungeon-texture","assets/tilesets/DungeonTile.png");
    assetManager->SplitTexture("dungeon-texture", "assets/tilesets/tiles_list_v1.3"); 
    assetManager->AddTexture("knight-texture", "assets/images/knight.png");

    


    auto& entity = manager.AddEntity("player", PLAYER_LAYER);
    //(int x, int y, int vX, int vY, int width, int height, float scale)
    entity.AddComponent<TransformComponent>(50, 50, 0, 0, 16, 16, 2.0f);
    //(std::string textureId, std::string sheetId, bool fixed)
    entity.AddComponent<SpriteComponent>("dungeon-texture", "lizard_m_idle_anim", true);
    //add anims
    auto spriteComp = entity.GetComponent<SpriteComponent>();
    spriteComp->MakeAnimFromSheet("knight_m_idle_anim", 90);
    spriteComp->MakeAnimFromSheet("knight_m_run_anim", 90);
    spriteComp->MakeAnimFromSheet("knight_m_hit_anim", 90);
    spriteComp->SetAnim("knight_m_idle_anim");
    entity.AddComponent<PlayerControl>();
    //spriteComp->HorzFlip(false);
    //MapManager(std::string textureId, int tileSize, float scale)
    map = std::make_unique<MapManager>("dungeon-texture", 16, 2);
    map->LoadMap("assets/tilemaps/TestMap.json", "Dungeon16x16"); //Tileset that map uses.

    //manager.ListEntities();
}

void Game::ProcessInput()
{
    Game::input->processInputs();
    switch (Game::input->keyEvents.type)
    {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            if (Game::input->keyEvents.key.keysym.sym == SDLK_ESCAPE)
                isRunning = false;
            break;
        default:
            break;
    }


}

void Game::Update()
{ 
    int delayTime = FRAME_RATE_TARGET - (SDL_GetTicks() - ticksLastFrame);
    if (delayTime > 0 && delayTime <= FRAME_RATE_TARGET)
    {
        SDL_Delay(delayTime);
    }
    float deltaTime = (SDL_GetTicks() - ticksLastFrame)/1000.0f;
    deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;
    ticksLastFrame = SDL_GetTicks();

    
    connectTCP->ServerRecvTCP();
    

    connectTCP->ClientRecvTCP();
    
    connectUDP->ServerRecvUDP();

    manager.Update(deltaTime);



}

void Game::Render()
{
    SDL_SetRenderDrawColor(renderer, 48, 48, 48, 255);
    SDL_RenderClear(renderer);

    //call Render of all entities
    manager.Render();

    SDL_RenderPresent(renderer);
}

void Game::Destroy()
{
    SDL_DestroyWindow(window);

    manager.ClearAll();

    SDLNet_Quit();
    IMG_Quit();
    SDL_Quit();
}






bool Game::Running() {
    return isRunning;
}


Game::~Game()
{
    Destroy();
}
