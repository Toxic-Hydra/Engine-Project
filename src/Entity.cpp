//
// Created by ivanl on 6/20/2020.
//

#include "Entity.h"
#include <iostream>

Entity::Entity(std::string name, EntityLayers layer)
{
	isActive = true; //Im going to think about separating this.
	destroy = false;
	this->name = name;
	this->layer = layer;
	parent = nullptr;
	child = nullptr;
}

EntityLayers Entity::GetLayer()
{
	return layer;
}

void Entity::SetActive(bool option)
{
	this->isActive = option;
}

bool Entity::IsActive()
{
	return isActive;
}

void Entity::Update(float deltaTime)
{
	for (auto& component : components)
	{
		component->Update(deltaTime);

	}
}

void Entity::Render()
{
	for (auto& component : components)
	{
		component->Render();
	}
}

bool Entity::GetDestroyed()
{
	return destroy;
}

void Entity::Destroy()
{
	//Later Removed by Entity Manager
	this->destroy = true;
}

void Entity::ListComponents()
{
	//for debug
	for (auto& component : components)
	{
		//the name is implementation defined which unfortunately will give us slightly different answers on different compilers.
		std::cout << " -" << typeid(component).name() << std::endl;
	}
}
