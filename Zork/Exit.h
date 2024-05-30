#pragma once

#include "Entity.h"

class Room;
class Item;

enum class Direction {
	North,
	East,
	West,
	South
};

class Exit : public Entity
{
public:
	Exit(string Name, string ContainerDescription, string LeadsToName, string LeadsToDescription, Room* ContainerRoom, Room* LeadsToRoom, Item* RequiredKey = nullptr);

	bool Unlock(const Item* UnlockKey);


	bool IsContainerRoom(const Room* SelectedRoom) const;

	Room* GetContainerRoom() const;
	Room* GetLeadsToRoom() const;
	
	string GetLeadsToDescription() const;

	Direction GetContainerDirection() const;
	Direction GetLeadsToDirection() const;

private:
	Room* Container;
	Room* LeadsTo;

	string LeadsToName;
	string LeadsToDescription;

	Item* Key;

	bool Locked;

	Direction ContainerDirection;
	Direction LeadsToDirection;
};

