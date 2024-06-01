#pragma once

#include "Entity.h"

class Room;
class Item;

class Exit : public Entity
{
public:
	Exit(string Name, string ContainerDescription, string ReversePathName, string ReversePathDescription, Room* ContainerRoom, Room* LeadsToRoom, Item* RequiredKey = nullptr);

	void Look() const override;
	void LookReverse() const;

	bool Unlock(const Item* UnlockKey);
	bool Lock(const Item* LockKey);

	bool IsContainerRoom(const Room* SelectedRoom) const;

	bool IsExitLocked() const;

	Room* GetContainerRoom() const;
	Room* GetLeadsToRoom() const;
	
	string GetReversePathName() const;

private:
	Room* Container;
	Room* LeadsTo;

	string ReversePathName;
	string ReversePathDescription;

	Item* Key;

	bool Locked;
};

