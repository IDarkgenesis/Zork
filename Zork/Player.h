#pragma once

#include"Creature.h"
#include<map>

class Item;
class Room;

class Player : public Creature
{
public:
	Player(string Name, string Description, Room* Location, int HitPoints = 1, int BaseDamage = 1);

	void Look() const override;

	bool Go(const string& Direction) override;

	bool Put(const string& ItemName, const string& Container);

	void RecieveDamage(Creature* Enemy, int DamageRecieved) override;

	bool UnlockDoor(const string& Direction, const string& Key);
	bool LockDoor(const string& Direction, const string& Key);
};

