#pragma once
#include "Component.h"
#include "TransformComponent.h"
#include "../Entity.h"
#include "../Animation.h"
#include "../Game.h"
#include "../TextureManager.h"
#include "../AssetManager.h"
#include <SDL.h>
#include <string>
#include <map>
#include "glm/glm.hpp"
#include <iostream>
#include <tuple>
class SpriteComponent : public Component
{
private: 
	SDL_Texture* texture;
	SDL_Rect* originRect; //Used to set our position in the texture
	std::vector<SDL_Rect*> originRects;
	SDL_Rect sourceRect;
	SDL_Rect destRect;
	int numFrames;
	//We get our x, y ,z, w, h from the transform;
	TransformComponent* transform;
	bool fixedOnScreen;
	SDL_RendererFlip flipFlag = SDL_FLIP_NONE;
	bool animated;
	//currently animations only left to right
	std::string currentAnim;
	int index = 0;
	int speed;
	std::map<std::string, Animation> animMap;
public:
	SpriteComponent(std::string textureId)
	{
		compType = "SpriteComponent";
		animated = false;
		fixedOnScreen = false;
		originRect = NULL;
		SetTexture(textureId);
	}

	SpriteComponent(std::string textureId, bool fixed)
	{
		compType = "SpriteComponent";
		animated = false;
		fixedOnScreen = fixed;
		originRect = NULL;
		SetTexture(textureId);
	}

	SpriteComponent(std::string textureId, std::string sheetId, bool fixed)
	{
		compType = "SpriteComponent"; 
		fixedOnScreen = fixed;
		SetTexture(textureId);
		SetRect(sheetId);
	}

	void SetTexture(std::string textureId)
	{

		texture = Game::assetManager->GetTexture(textureId);
		std::cout << "Set texture: " << textureId << std::endl;
	}

	void SetRect(std::string sheetId)
	{
		SDL_Rect newRect;
		
		std::tie(newRect, numFrames) = Game::assetManager->GetSheetRect(sheetId);
		originRect = new SDL_Rect{ newRect.x, newRect.y, newRect.w, newRect.h };
		//std::cout << numFrames << " " << newRect.x << std::endl;
		if (numFrames == 0)
			animated = false;
	}

	void SetAnim(std::string animation)
	{
		if (currentAnim.compare(animation) == 0)
			return;
		//should do a check for valid anim;
		this->numFrames = animMap[animation].numFrames;
		this->speed = animMap[animation].speed;
		this->index = animMap[animation].index;
		this->currentAnim = animation;

		sourceRect.x = originRects[index]->x;
		sourceRect.y = originRects[index]->y;
		sourceRect.w = originRects[index]->w;
		sourceRect.h = originRects[index]->h;

	}


	void MakeAnimFromSheet(std::string sheetId, int speed)
	{
		SDL_Rect newRect;
		int frames;
		std::tie(newRect, frames) = Game::assetManager->GetSheetRect(sheetId);

		originRects.emplace_back(new SDL_Rect{ newRect.x, newRect.y, newRect.w, newRect.h });
		Animation newAnim{ index, frames, speed };
		animMap.emplace(sheetId, newAnim);
		index++;
	}

	void HorzFlip(bool flip)
	{
		if (flip)
			flipFlag = SDL_FLIP_HORIZONTAL;
		else
			flipFlag = SDL_FLIP_NONE;
	}

	void Start() override
	{
		//std::weak_ptr<TransformComponent> wTransform = owner->GetComponent<TransformComponent>();
		transform = owner->GetComponent<TransformComponent>();//wTransform.lock();
		sourceRect.x = 0;
		sourceRect.y = 0;
		sourceRect.w = transform->width;
		sourceRect.h = transform->height;
		if (originRect != NULL)
		{
			//TODO: THIS IS NOT BEING SET
			
			//TODO: New constructor that updates transform sizes based on origin rect
			//I need to iterate the rect that defines our sprite
			//if i iterate originRect and change it, it will change for
			//all other instances. not ideal, so we copy it instead.
			sourceRect.x = originRect->x;
			sourceRect.y = originRect->y;
			sourceRect.w = originRect->w;
			sourceRect.h = originRect->h;
			transform->width = sourceRect.w = originRect->w;
			transform->height = sourceRect.h = originRect->h;
			//std::cout << "Rect is set: " << transform->width << std::endl;
		}
	}
	void Update(float deltaTime) override
	{
		//update animations
		if (animated)
		{
			sourceRect.x = sourceRect.w * static_cast<int>((SDL_GetTicks() / speed) % numFrames) + (originRects.size() > 0 ? originRects[index]->x : 0);
		}

		destRect.x = static_cast<int>(transform->position.x); //TODO: Compensate for camera
		destRect.y = static_cast<int>(transform->position.y); //TODO: Compensate for camera

		destRect.w = transform->width * static_cast<int>(transform->scale);
		destRect.h = transform->height * static_cast<int>(transform->scale);
	}
	void Render() override
	{
		TextureManager::Render(texture, sourceRect, destRect, flipFlag);
	}
	//we are not in charge of destroying texture or source.
};

