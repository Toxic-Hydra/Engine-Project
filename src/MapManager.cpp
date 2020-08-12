//
// Created by ivanl on 2020/6/29
//
#include "MapManager.h"
#include "../lib/tile/tileson.h"
#include "AssetManager.h"
#include "Game.h"
#include "EntityManager.h"
#include "components/TileComponent.h"
#include <string>
#include <filesystem>

MapManager::MapManager(std::string textureId, int tileSize, int scale) :
	textureId(textureId), tileSize(tileSize), scale(scale){}

void MapManager::LoadMap(std::string mapName, std::string tilesetName)
{
	map = parser.parse(std::filesystem::path(mapName));
	if (map.getStatus() != tson::ParseStatus::OK)
	{
		
		std::cout << map.getStatusMessage();
		return;
	}

	tson::Layer *baseLayer = map.getLayer("Tile Layer 1");
	tson::Tileset* tileSet = map.getTileset(tilesetName); //tileset name used by tiled so .tsx
	

	int firstId = tileSet->getFirstgid();
	//although the map texture size is only 7xsomething, we need the size of the whole texture to determine the offsets later.
	int columns = tileSet->getColumns(); 
	int row = tileSet->getTileCount() / columns;
	int lastId = (tileSet->getFirstgid() + tileSet->getTileCount() - 1);

	if (baseLayer->getType() == tson::LayerType::TileLayer)
	{
		for (auto& [pos, tile] : baseLayer->getTileData())
		{
			tson::Vector2i position = { std::get<0>(pos) * map.getTileSize().x * scale, std::get<1>(pos) * map.getTileSize().y * scale };
			int baseTilePos = (tile->getId() - firstId);

			int tileModX = (baseTilePos % columns);
			int currRow = (baseTilePos / columns);
			//Texture offsets
			int offSetX = (tileModX != 0) ? ((tileModX)*map.getTileSize().x) : (0 * map.getTileSize().x);
			int offSetY = (currRow < row - 1) ? (currRow * map.getTileSize().y) : ((row - 1) * map.getTileSize().y);
			
			AddTile(offSetX, offSetY, position.x, position.y);
		}
	}
}

extern EntityManager manager;
void MapManager::AddTile(int sourceX, int sourceY, int x, int y)
{
	Entity& newTile = manager.AddEntity("Tile", EntityLayers::TILE_BACKGROUND_LAYER);
	
	//TileComponent(std::string tileSet, int x, int y, int sRectX, int sRectY, int tileSize, int tileScale)
	newTile.AddComponent<TileComponent>(textureId, x, y, sourceX, sourceY, tileSize, static_cast<int>(scale));
}
