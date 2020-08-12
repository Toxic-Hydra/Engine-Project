//
// Created by ivanl on 6/20/2020.
//

#ifndef ENGINE_ENTITY_H
#define ENGINE_ENTITY_H


#include "EngineConstants.h"
#include "components/Component.h"
#include <typeinfo>
#include <string>
#include <fstream>
#include <map>
#include <memory>
#include <vector>


class Entity {
private:
    //Hoping to add some Unity style hierarchy
    Entity* parent;
    Entity* child;
    bool isActive; //If active it updates
    bool destroy; //if true it will be queues for destruction
    
    EntityLayers layer;
    std::vector<Component*> components;
    //map of all components
    std::map<const char*, Component*> cTypeMap;
public:
    std::string name;
    Entity(std::string name, EntityLayers layer);
    EntityLayers GetLayer();

    //TODO: ADD CHILD, ADD PARENT, NAVIGATE CHILDREN

    void SetActive(bool option);
    bool IsActive();
    void Update(float deltaTime);
    void Render();
    bool GetDestroyed();
    void Destroy();
    void Serialize(std::ofstream &out);
    void DeSerialize(std::ifstream &in);


    template <typename T, typename... Targs>
    T& AddComponent(Targs&&... args)
    {
        T* newComponent(new T(std::forward<Targs>(args)...));
        newComponent->owner = this;
        components.emplace_back(newComponent);
        cTypeMap[typeid(*newComponent).name()] = newComponent;
        //cTypeMap.emplace(newComponent->compType, newComponent);
        newComponent->Start();
        return *newComponent;
    }

    template<typename T>
    T* GetComponent()
    {
        
        return static_cast<T*>(cTypeMap[typeid(T).name()]);
    }
    //maybe I'll combine hasComponent and GetComponent,
    //I can think of a few issues with that though
    //mainly checks in code that uses this.
    template<typename T>
    bool HasComponent()
    {
        //return(noexcept(cTypeMap.at(&typeid(T))));
        //apparently a better way of doing this is to just count the map key
        return cTypeMap.count(typeid(T).name());
    }

    //TODO: Required component function, usefull for prefabs.

    void ListComponents();

};


#endif //ENGINE_ENTITY_H
