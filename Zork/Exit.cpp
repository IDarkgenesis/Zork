#include "Exit.h"
#include "Item.h"
#include "Room.h"

Exit::Exit(string Name, string ContainerDescription, string ReversePathName, string ReversePathDescription, Room* ContainerRoom, Room* LeadsToRoom, Item* RequiredKey)
	: Entity(Name, ContainerDescription)
{
	this->ReversePathName = ReversePathName;
	this->ReversePathDescription = ReversePathDescription;

	Container = ContainerRoom;
	LeadsTo = LeadsToRoom;

	Locked = false;
	if (RequiredKey && RequiredKey->GetItemType() == ItemType::Key) {
		Key = RequiredKey;
		Locked = true;
	}

	Container->AddExit(this);
	LeadsTo->AddExit(this);
}

void Exit::Look() const
{
	cout << Description << endl;
}

void Exit::LookReverse() const
{
	cout << ReversePathDescription << endl;
}

bool Exit::Unlock(const Item* UnlockKey)
{
	if (UnlockKey && UnlockKey == Key)
	{
		Locked = false;
		return true;
	}

	return false;
}

bool Exit::IsContainerRoom(const Room* SelectedRoom) const
{
	if (SelectedRoom && SelectedRoom == Container)
	{
		return true;
	}

	return false;
}

bool Exit::IsExitLocked() const
{
	return Locked;
}

Room* Exit::GetContainerRoom() const
{
	return Container;
}

Room* Exit::GetLeadsToRoom() const
{
	return LeadsTo;
}

string Exit::GetReversePathName() const
{
	return ReversePathName;
}