//
// Created by ivanl on 2020/7/5
//

#pragma once
#include <SDL.h>
#include <string>

class Input
{
private:
	//TODO: Improve input handling: https://stackoverflow.com/questions/3741055/inputs-in-sdl-on-key-pressed
	//TODO: https://gamedev.stackexchange.com/questions/89755/how-to-handle-multiple-events-in-sdl2-and-c
	std::string up, left, down, right;
	std::string key_curr, key_prev;
	int horz_dir;
	int vert_dir;
	std::string ConString(std::string key);
public:

	SDL_Event keyEvents;
	Input();
	Input(std::string up, std::string left, std::string down, std::string right);
	void processInputs();
	void SetInput(std::string up, std::string left, std::string down, std::string right);
	int key_horz();
	int key_vert();



};

