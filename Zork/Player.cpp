#include "Player.h"
#include "Room.h"
#include "Item.h"

Player::Player(string Name, string Description, Room* Location, int HitPoints, int BaseDamage) :
	Creature(Name, Description, Location, HitPoints, BaseDamage)
{
	Go(Location);
}

bool Player::Go(Room* NewLocation)
{
	if (Location && NewLocation)
	{
		Location->PlayerLeaves();
		NewLocation->PlayerEnters(this);
		Location = NewLocation;
		return true;
	}

	return false;
}

bool Player::Pick(Item* NewItem)
{
	if (!NewItem) return false;

	auto it = Inventory.find(NewItem->GetName());

	if (it == Inventory.cend())
	{
		Inventory.insert(pair<string, Item*>(NewItem->GetName(), NewItem));
		return true;
	}
	return false;
}

bool Player::Drop(Item* OutItem)
{	
	if (!OutItem) return false;

	auto it = Inventory.find(OutItem->GetName());

	if (it != Inventory.cend())
	{
		Inventory.erase(it);
	}

	return false;
}

void Player::RecieveDamage(Creature* Enemy, int DamageRecieved)
{
	HitPoints -= DamageRecieved;
}
