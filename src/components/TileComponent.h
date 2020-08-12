//
// Created by ivanl on 2020/6/29
//

#pragma once
#include "Component.h"
#include "../../lib/math/glm/glm.hpp"
#include "../Game.h"
#include "../TextureManager.h"
#include <SDL.h>
#include <string>
#include <iostream>

class TileComponent : public Component
{
public:
	glm::vec2 position;
	SDL_Texture* texture;
	SDL_Rect sRect;
	SDL_Rect dRect;

	TileComponent(std::string tileSet, int x, int y, int sRectX, int sRectY, int tileSize, int tileScale)
	{
		texture = Game::assetManager->GetTexture(tileSet);
		std::cout << tileSet << " " << sRectX << " " << sRectY << std::endl;
		if (texture == NULL)
		{
			std::cout << SDL_GetError() << std::endl;
		}

		sRect.x = sRectX;
		sRect.y = sRectY;
		sRect.w = tileSize;
		sRect.h = tileSize;

		dRect.x = x;
		dRect.y = y;
		dRect.w = tileSize * tileScale;
		dRect.h = tileSize * tileScale;

		position.x = x;
		position.y = y;

	}

	~TileComponent()
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
	}

	void Update(float deltaTime) override
	{
		dRect.x = static_cast<int>(position.x); //- camera.x
		dRect.y = static_cast<int>(position.y); //-camera
	}

	void Render() override
	{
		TextureManager::Render(texture, sRect, dRect, SDL_FLIP_NONE);
	}

};

