//
// Created by ivanl on 6/20/2020.
//

#include "TextureManager.h"

#include <iostream>

SDL_Texture *TextureManager::LoadTexture(const char *filePath) {
    SDL_Surface* surface = IMG_Load(filePath);
    if(!surface)
    {
        std::cout << "FAILED TO LOAD IMAGE: " << IMG_GetError() << std::endl;
    }
    SDL_Texture* loadedTexture = SDL_CreateTextureFromSurface(Game::renderer, surface);
    if(loadedTexture == NULL)
    {
        std::cerr << "FAILED TO LOAD TEXTURE: " << SDL_GetError() << std::endl;
    }

    SDL_FreeSurface(surface);
    return loadedTexture;
}

void TextureManager::Render(SDL_Texture *texture, SDL_Rect source, SDL_Rect dest, SDL_RendererFlip flipFlag)
{
    //Using RenderCopyEx gives us more options, like scrolling a rect through our texture for a specific part
    //very usefull for sprites or tiles when we don't want to render a whole texture
    //for now angle and center are nothing. can probably use angle for rotations later.
    if(SDL_RenderCopyEx(Game::renderer, texture, &source, &dest, 0, NULL, flipFlag) != 0)
    {
        std::cout << "RENDER ERROR" << std::endl;
        std::cerr << "RENDER TEXTURE ERROR: " << SDL_GetError() << std::endl;
    }


}
