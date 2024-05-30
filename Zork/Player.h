#pragma once

#include"Creature.h"
#include<map>

class Item;
class Room;

class Player : public Creature
{
public:
	Player(string Name, string Description, Room* Location, int HitPoints = 1, int BaseDamage = 1);

	void Go(Room* NewLocation) override;

	void Pick(Item* Item);

	void Drop(Item* Item);

	void RecieveDamage(Creature* Enemy, int DamageRecieved) override;

private:

	map<string, Item*> Inventory;
};

