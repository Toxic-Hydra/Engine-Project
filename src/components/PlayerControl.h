//
// Created by ivanl on 2020/6/24
//

#pragma once

#include "Component.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "../Game.h"
#include "../Entity.h"

#include <SDL.h>

class PlayerControl : public Component
{
private:
	TransformComponent* transform;
	SpriteComponent* sprite;
	
	float speed = 50.0f;
	
public:
	
	PlayerControl() 
	{
		
	}
	

	void Start() override
	{
		transform = owner->GetComponent<TransformComponent>();
		sprite = owner->GetComponent<SpriteComponent>();
	}

	void Update(float deltaTime) override
	{
		

		if (transform->velocity.x < 0)
		{
			sprite->HorzFlip(true);
			sprite->SetAnim("knight_m_run_anim");
		}
		else if(transform->velocity.x > 0)
		{
			sprite->HorzFlip(false);
			sprite->SetAnim("knight_m_run_anim");
		}
		else
		{
			sprite->SetAnim("knight_m_idle_anim");
		}

		transform->velocity.x = speed * Game::input->key_horz();
		transform->velocity.y = speed * Game::input->key_vert();
		
	}
	void Render() override
	{

	}

};

