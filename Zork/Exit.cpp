#include "Exit.h"
#include "Item.h"

Exit::Exit(string Name, string ContainerDescription, string LeadsToName, string LeadsToDescription, Room* ContainerRoom, Room* LeadsToRoom, Item* RequiredKey)
	: Entity(Name, ContainerDescription)
{
	this->LeadsToName = LeadsToName;
	this->LeadsToDescription = LeadsToDescription;

	Container = ContainerRoom;
	LeadsTo = LeadsToRoom;

	Locked = false;
	if (RequiredKey) {
		Key = RequiredKey;
		Locked = true;
	}
}

bool Exit::Unlock(const Item* UnlockKey)
{
	if (UnlockKey == Key)
	{
		Locked = false;
		return true;
	}

	return false;
}

bool Exit::IsContainerRoom(const Room* SelectedRoom) const
{
	if (SelectedRoom == Container)
	{
		return true;
	}

	return false;
}

Room* Exit::GetContainerRoom() const
{
	return Container;
}

Room* Exit::GetLeadsToRoom() const
{
	return LeadsTo;
}

string Exit::GetLeadsToDescription() const
{
	return LeadsToDescription;
}

Direction Exit::GetContainerDirection() const
{
	return ContainerDirection;
}

Direction Exit::GetLeadsToDirection() const
{
	return LeadsToDirection;
}
