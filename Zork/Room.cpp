#include "Room.h"
#include "Player.h"
#include "Npc.h"
#include "Item.h"
#include "Exit.h"

Room::Room(string Name, string Description) : Entity(Name, Description)
{
	CurrentPlayer = nullptr;
}

void Room::Look() const
{
	cout << Name + ": " << Description << endl;
}

bool Room::IsPlayerInRoom() const
{
	return CurrentPlayer != nullptr;
}

Player* Room::GetPlayerInRoom() const
{
	return CurrentPlayer;
}

void Room::PlayerEnters(Player* NewPlayer)
{
	if (NewPlayer)
	{
		CurrentPlayer = NewPlayer;
	}
}

void Room::PlayerLeaves()
{
	CurrentPlayer = nullptr;
}

bool Room::AddItem(Item* NewItem)
{
	if (!NewItem) return false;

	auto it = Items.find(NewItem->GetName());

	if (it == Items.cend()) 
	{
		Items.insert(pair<string, Item*>(NewItem->GetName(), NewItem));
		return true;
	}

	return false;
}

bool Room::RemoveItem(Item* OutItem)
{
	if (!OutItem) return false;

	auto it = Items.find(OutItem->GetName());

	if (it != Items.cend())
	{
		Items.erase(it);
		return true;
	}

	return false;
}

bool Room::AddNpc(Npc* NewNpc)
{
	if (!NewNpc) return false;

	auto it = Npcs.find(NewNpc->GetName());

	if (it == Npcs.cend())
	{
		Npcs.insert(pair<string, Npc*>(NewNpc->GetName(), NewNpc));
		return true;
	}
	return false
}

bool Room::RemoveNpc(Npc* OutNpc)
{
	if (!OutNpc) return false;

	auto it = Npcs.find(OutNpc->GetName());

	if (it != Npcs.cend())
	{
		Npcs.erase(it);
		return true;
	}

	return false;
}

void Room::AddExit(Exit* NewExit)
{
	if (NewExit)
	{
		string exitName = NewExit->IsContainerRoom(this) ? NewExit->GetName() : NewExit->GetLeadsToName();
		auto it = Exits.find(exitName);

		if (it == Exits.cend())
		{
			Exits.insert(pair<string, Exit*> (exitName, NewExit));
		}
	}
}

