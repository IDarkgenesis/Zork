#pragma once

#include "Entity.h"
#include <map>

using namespace std;

class Exit;
class Item;
class Npc;
class Player;
class Creature;

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
	Item* GetItem(const string& ItemName) const;

	bool AddNpc(Npc* NewNpc);
	bool RemoveNpc(Npc* OutNpc);
	Creature* GetCreature(const string& NpcName) const;

	void AddExit(Exit* NewExit);
	Exit* GetExit(const string& ExitName) const;
	map<string, Exit*> GetExitList() const;

private:
	map<string, Exit*> Exits;
	map<string, Item*> Items;
	map<string, Npc*> Npcs;

	Player* CurrentPlayer;
};

