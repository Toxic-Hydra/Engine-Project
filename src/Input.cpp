#include "Input.h"

std::string Input::ConString(std::string key)
{
	return std::to_string(static_cast<int>(key[0]));
}

Input::Input():
	up(std::to_string(SDLK_UP)), left(std::to_string(SDLK_LEFT)),
	down(std::to_string(SDLK_DOWN)), right(std::to_string(SDLK_RIGHT)),
	horz_dir(0), vert_dir(0)
{}

Input::Input(std::string up, std::string left, std::string down, std::string right):
	up(ConString(up)), left(ConString(left)), down(ConString(down)), right(ConString(right)), horz_dir(0), vert_dir(0)
{}


void Input::processInputs()
{
	SDL_PollEvent(&keyEvents);
}

void Input::SetInput(std::string up, std::string left, std::string down, std::string right)
{
}

//Keyboard events only take place when a keys state changes from being unpressed to pressed, and vice versa.
int Input::key_horz()
{
	//need to change the output for key down, and key up.
	if (keyEvents.type == SDL_KEYDOWN)
	{
		key_prev = key_curr;
		key_curr = std::to_string(keyEvents.key.keysym.sym);
		
		if (key_curr.compare(left) == 0)
		{
			horz_dir = -1;
		}
		if (key_curr.compare(right) == 0)
		{
			horz_dir = 1;
		}
	}
	if (keyEvents.type == SDL_KEYUP)
	{

		key_curr = std::to_string(keyEvents.key.keysym.sym);
		
		if (key_curr.compare(left) == 0)
		{
			horz_dir = 0;
		}
		if (key_curr.compare(right) == 0)
		{
			horz_dir = 0;
		}
	}



	return horz_dir;
}

int Input::key_vert()
{
	if (keyEvents.type == SDL_KEYDOWN)
	{
		key_curr = std::to_string(keyEvents.key.keysym.sym);
		if (key_curr.compare(up) == 0)
		{
			vert_dir = -1;

		}
		if (key_curr.compare(down) == 0)
		{
			vert_dir = 1;
		}
		
	}
	if (keyEvents.type == SDL_KEYUP)
	{

		key_curr = std::to_string(keyEvents.key.keysym.sym);
		if (key_curr.compare(up) == 0)
		{
			vert_dir = 0;
		}
		if (key_curr.compare(down) == 0)
		{
			vert_dir = 0;
		}
		
	}

	return vert_dir;
}
