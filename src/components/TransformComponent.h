#pragma once
#include "glm/glm.hpp"
#include "Component.h"
class TransformComponent : public Component
{
public:
	glm::vec2 position;
	glm::vec2 velocity;
	float scale;
	int width;
	int height;
	TransformComponent():
		position(glm::vec2(0, 0)), velocity(glm::vec2(0,0)),
		scale(1), width(1), height(1)
	{
		compType = "TransformComponent";
	}
	TransformComponent(int x, int y, int vX, int vY, int width, int height, float scale):
		position(glm::vec2(x, y)), velocity(glm::vec2(vX, vY)),
		scale(scale), width(width), height(height)
	{
		compType = "TransformComponent";
	}

	//None of the overrides here actually do anything, why override?
	void Start() override
	{

	}


	void Update(float deltaTime) override
	{
		position += velocity * deltaTime;
	}

	void Render() override
	{

	}

	void Serialize(std::ostream& out)
	{
		/*glm::vec2 position;
	glm::vec2 velocity;
	float scale;
	int width;
	int height;*/
		out << "Transform" << '\n' << owner->name << '\n';
		out << position.x << '\n' << position.y << '\n';
		out << velocity.x << '\n' << velocity.y << '\n';
		out << scale << '\n';
		out << width << '\n';
		out << height << '\n';
	}

	void DeSerialize(std::istream& in)
	{
		//assuming we are past the "Transform" line

		in >> position.x >> position.y;
		in >> velocity.x >> velocity.y;
		in >> scale;
		in >> width;
		in >> height;
	}
};

