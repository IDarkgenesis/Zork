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
	Entity::Look();

	cout << endl;
	for (auto Exit : Exits)
	{
		if (Exit.second->IsContainerRoom(this))
		{
			Exit.second->Look();
		}
		else 
		{
			Exit.second->LookReverse();
		}
	}

	if (Items.size() > 0) {
		cout << endl << "Looking carefully you see:" << endl;
		for (auto item : Items)
		{
			item.second->Look();
		}
	}

	if (Npcs.size() > 0)
	{
		cout << endl << "You are not alone in this space" << endl;
		for (auto np : Npcs)
		{
			np.second->Look();
		}
	}
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
		Look();
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

Item* Room::GetItem(const string& ItemName) const
{
	auto it = Items.find(ItemName);
	if (it != Items.cend())
	{
		return it->second;
	}
	return nullptr;
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
	return false;
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

Creature* Room::GetCreature(const string& CreatureName) const
{
	// Check if creature is player
	if (CreatureName == "Player")
	{
		return CurrentPlayer;
	}
	// Target is an NPC
	else 
	{
		auto it = Npcs.find(CreatureName);
		if (it != Npcs.cend())
		{
			return it->second;
		}
	}
	return nullptr;
}

void Room::AddExit(Exit* NewExit)
{
	if (NewExit)
	{
		string exitName = NewExit->IsContainerRoom(this) ? NewExit->GetName() : NewExit->GetReversePathName();
		auto it = Exits.find(exitName);

		if (it == Exits.cend())
		{
			Exits.insert(pair<string, Exit*> (exitName, NewExit));
		}
	}
}

Exit* Room::GetExit(const string& ExitName) const
{
	auto it = Exits.find(ExitName);
	if (it != Exits.cend()) return it->second;
	return nullptr;
}

map<string, Exit*> Room::GetExitList() const
{
	return Exits;
}

