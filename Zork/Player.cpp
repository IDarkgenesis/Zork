#include "Player.h"
#include "Room.h"
#include "Item.h"

Player::Player(string Name, string Description, Room* Location, int HitPoints, int BaseDamage) :
	Creature(Name, Description, Location, HitPoints, BaseDamage)
{
	Go(Location);
}

void Player::Go(Room* NewLocation)
{
	if (Location)
	{
		Location->PlayerLeaves();
	}
	if (NewLocation)
	{
		NewLocation->PlayerEnters(this);

		Location = NewLocation;
	}
}

void Player::Pick(Item* NewItem)
{
	auto it = Inventory.find(NewItem->GetName());

	if (it == Inventory.cend())
	{
		Inventory.insert(pair<string, Item*>(NewItem->GetName(), NewItem));
	}
}

void Player::Drop(Item* OutItem)
{
	auto it = Inventory.find(OutItem->GetName());

	if (it != Inventory.cend())
	{
		Inventory.erase(it);
	}
}

void Player::RecieveDamage(Creature* Enemy, int DamageRecieved)
{
	HitPoints -= DamageRecieved;
}
