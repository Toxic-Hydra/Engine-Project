//
// Created by ivanl on 2020/6/21
//

#include "EntityManager.h"
#include <iostream>

EntityManager::EntityManager()
{
	entities.resize(LAYERNUM);
}

void EntityManager::Update(float deltaTime)
{
	for (int i = 0; i < LAYERNUM; i++)
	{
		
		if (entities[i].size() != 0)
		{
			auto it = std::begin(entities[i]);
			for (auto& entity : entities[i])
			{
				if (entity->GetDestroyed())
					EraseDestroyed(*entity, it, entity->GetLayer());
				if (entity->IsActive())
					entity->Update(deltaTime);
				it++;
			}
		}
	}
}

void EntityManager::Render()
{
	//practically identical to our update.
	for (int i = 0; i < LAYERNUM; i++)
	{
		if (entities[i].size() != 0)
		{
			for (auto& entity : entities[i])
			{
				if (entity->IsActive())
				{
					
					entity->Render();
				}
			}
		}
	}
}

bool EntityManager::HasEntities()
{
	for (int i = 0; i < LAYERNUM; i++)
	{
		if (entities[i].size() > 0)
			return true;
	}

	return false;
}

void EntityManager::EraseDestroyed(Entity entity, std::vector<std::shared_ptr<Entity>>::iterator it, EntityLayers layer)
{
	if (entity.GetDestroyed())
		entities[layer].erase(it);
}

Entity& EntityManager::AddEntity(std::string entityId, EntityLayers layer) 
{
	std::shared_ptr<Entity> entity (std::make_shared<Entity>(entityId, layer));
	entities[static_cast<int>(layer)].emplace_back(entity);
	return *entity;
}

int EntityManager::EntityCount() const
{
	int count = 0;
	for (int i = 0; i < LAYERNUM; i++)
	{
		count = entities[i].size();
	}

	return count;
}

void EntityManager::ListEntities()
{
	for (int i = 0; i < LAYERNUM; i++)
	{
		for (auto& entity : entities[i])
		{
			std::cout << "-" << entity->name << std::endl;
		}
	}
}

void EntityManager::ClearAll()
{
	entities.clear();
}
