//
// Created by ivanl on 6/20/2020.
//

#ifndef ENGINE_TEXTUREMANAGER_H
#define ENGINE_TEXTUREMANAGER_H

#include <SDL.h>
#include <SDL_image.h>
#include "Game.h"

class TextureManager
{
public:
    static SDL_Texture* LoadTexture(const char* filePath);
    static void Render(SDL_Texture* texture, SDL_Rect source, SDL_Rect dest, SDL_RendererFlip flipFlag);
};


#endif //ENGINE_TEXTUREMANAGER_H
