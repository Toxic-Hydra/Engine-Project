//
// Created by ivanl on 2020/6/21
//

#pragma once
#include "EngineConstants.h"
#include "Entity.h"
#include <map>
#include <string>
#include <memory>


class EntityManager
{
private:
	
	std::vector<std::vector<std::shared_ptr<Entity>>> entities;
	//this may not be the best solution. but it's arranged like this for rendering
	//SDL provides no z order so i'll shittily implement painters myself for now.
	//Frankly i'm thinking of writing a new renderer or seperating into 1 main list + 
	//several layer lists so only one of these functions is a mess.
public:
	EntityManager();
	void Update(float deltaTime);
	void Render();

	bool HasEntities();
	void EraseDestroyed(Entity entity, std::vector<std::shared_ptr<Entity>>::iterator it, EntityLayers layer);
	Entity& AddEntity(std::string entityId, EntityLayers layer);
	//Should we do a get entities? might need for serialization
	int EntityCount() const;
	void ListEntities();

	void ClearAll();



};

