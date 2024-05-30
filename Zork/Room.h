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

	bool AddItem(Item* NewItem);
	bool RemoveItem(Item* OutItem);

	bool AddNpc(Npc* NewNpc);
	bool RemoveNpc(Npc* OutNpc);

	void AddExit(Exit* NewExit);

private:
	map<string, Exit*> Exits;
	map<string, Item*> Items;
	map<string, Npc*> Npcs;

	Player* CurrentPlayer;
};

