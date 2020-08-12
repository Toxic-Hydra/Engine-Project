//
// Created by ivanl on 2020/6/29
//
#include "EngineConstants.h"
#include "EntityManager.h"

#include "../lib/tile/tileson.h"
#include <SDL.h>
#include <string>
#pragma once
class MapManager
{
private:
	std::string mapName;
	int tileSize;
	int scale;
	std::string textureId;
	tson::Tileson parser;
	tson::Map map;
	void AddTile(int sourceX, int sourceY, int x, int y);
public:
	MapManager(std::string textureId, int tileSize, int scale);
	void LoadMap(std::string mapName, std::string tilesetName);
	

};

