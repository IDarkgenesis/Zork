#pragma once

#include "Entity.h"
#include<map>

class Room;
class Item;

class Creature : public Entity
{
public:
	Creature(string Name, string Description, Room* Location, int HitPoints, int BaseDamage);

	virtual bool Go(const string& Direction);

	bool Attack(const string& Target);
	bool Attack();

	bool Pick(const string& ItemName);
	bool Drop(const string& ItemName);

	bool EquipItem(const string& ItemName);
	bool UnequipItem(const string& ItemName);
	
	void AutoEquip(Item* EquipItem);

	virtual void RecieveDamage(Creature* Enemy, int DamageRecieved);

	bool IsAlive() const;
	bool HasTarget() const;

	void HandleDeath();

	Room* GetCurrentLocation() const;

	pair<Item*, Item*> GetItemFromInventory(const string& ItemName) const;
	
	bool AddItemToInventory(Item* OutItem);

protected:
	Room* Location;
	
	int HitPoints;

	int BaseDamage;

	Creature* CurrentTarget;

	map<string, Item*> Inventory;

	
	bool RemoveItemFromInventory(Item* NewItem);
	
	Item* EquippedWeapon;
	Item* EquippedArmor;
};

