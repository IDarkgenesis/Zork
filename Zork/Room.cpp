#include "Room.h"
#include "Player.h"
#include "Npc.h"
#include "Item.h"

Room::Room(string Name, string Description) : Entity(Name, Description)
{
	CurrentPlayer = nullptr;
}

void Room::Look() const
{
	cout << Name + ": " << Description << endl;
}

bool Room::IsPlayerInRoom()
{
	return CurrentPlayer != nullptr;
}

Player* Room::GetPlayerInRoom()
{
	return CurrentPlayer;
}

void Room::PlayerEnters(Player* NewPlayer)
{
	CurrentPlayer = NewPlayer;
}

void Room::PlayerLeaves()
{
	CurrentPlayer = nullptr;
}

void Room::AddItem(Item* NewItem)
{
	auto it = Items.find(NewItem->GetName());

	if (it == Items.cend()) 
	{
		Items.insert(pair<string, Item*>(NewItem->GetName(), NewItem));
	}
}

void Room::RemoveItem(Item* OutItem)
{
	auto it = Items.find(OutItem->GetName());

	if (it != Items.cend())
	{
		Items.erase(it);
	}
}

void Room::AddNpc(Npc* NewNpc)
{
	auto it = Npcs.find(NewNpc->GetName());

	if (it == Npcs.cend())
	{
		Npcs.insert(pair<string, Npc*>(NewNpc->GetName(), NewNpc));
	}
}

void Room::RemoveNpc(Npc* OutNpc)
{
	auto it = Npcs.find(OutNpc->GetName());

	if (it != Npcs.cend())
	{
		Npcs.erase(it);
	}
}

