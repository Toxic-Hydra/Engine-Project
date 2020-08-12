//
// Created by ivanl on 6/20/2020.
//

#ifndef ENGINE_COMPONENT_H
#define ENGINE_COMPONENT_H

/*
//forward decl
class Entity;
template<typename T>
std::shared_ptr<T> Entity::GetComponent() const;
*/
class Entity;
#include <string>
#include <fstream>

class Component 
{
public:
	Entity* owner;
	std::string compType;
	virtual void Start() {};
	virtual void Update(float deltaTime) {};
	virtual void Render() {};
	virtual void Serialize(std::ofstream& out) {};
	virtual void DeSerialize(std::ifstream& in) {};
	virtual ~Component() {};
};


#endif //ENGINE_COMPONENT_H
