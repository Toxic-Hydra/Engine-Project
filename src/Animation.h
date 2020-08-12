//
// Created by ivanl on 2020/6/23
//

#pragma once
#include <string>

class Animation
{
public:
	int numFrames;
	int index;
	int speed;
	Animation(int index, int frames, int speed)
		:numFrames(frames), index(index), speed(speed)
	{

	}
	Animation()
	{

	}
};

