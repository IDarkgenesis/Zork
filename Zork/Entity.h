#pragma once

#include <iostream>
#include <map>

using namespace std;

enum class EntityType
{
	ITEM,
	ROOM,
	EXIT,
	PLAYER,
	NPC
};

class Entity
{
public:
	Entity(string Name, string Description, EntityType Type, Entity* Partent = nullptr);

	virtual void Tick();

	void Look() const;

	void AddToContainer(Entity* Child);

	void RemoveFromContainer(Entity* Child);

protected:
	string Name;

	string Description;

	EntityType Type;

	Entity* Parent;

	map<string, Entity*> Container;
};

