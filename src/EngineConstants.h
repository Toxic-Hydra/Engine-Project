//
// Created by ivanl on 6/20/2020.
//

#ifndef ENGINE_ENGINECONSTANTS_H
#define ENGINE_ENGINECONSTANTS_H
#include <string>


const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const unsigned int FPS = 60;
const unsigned int FRAME_RATE_TARGET = 1000 / FPS;

const int MAX_CLIENTS = 16;
const unsigned short SERVER_PORT = 0451;
const unsigned short CLIENT_PORT = 0452;
const std::string LOCAL_HOST = "127.0.0.1";

enum EntityLayers
{
	TILE_BACKGROUND_LAYER = 0,
	TILE_MID_LAYER = 1,
	PLAYER_LAYER = 2,
	ENEMY_LAYER = 3,
	PROJECTILE_LAYER = 4,
	COVER_LAYER = 5,
	TILE_FOREGROUND_LAYER = 6

};

const int LAYERNUM = 7;

#endif //ENGINE_ENGINECONSTANTS_H
