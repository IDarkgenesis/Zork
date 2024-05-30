#pragma once

#include "Entity.h"
#include <map>

using namespace std;

class Exit;
class Item;
class Npc;
class Player;

class Room : public Entity
{
public:
	Room(string Name, string Description);

	void Look() const override;

	bool IsPlayerInRoom() const;

	Player* GetPlayerInRoom() const;

	void PlayerEnters(Player* Player);
	void PlayerLeaves();

	void AddItem(Item* NewItem);
	void RemoveItem(Item* OutItem);

	void AddNpc(Npc* NewNpc);
	void RemoveNpc(Npc* OutNpc);

private:
	map<string, Exit*> Exits;
	map<string, Item*> Items;
	map<string, Npc*> Npcs;

	Player* CurrentPlayer;
};

