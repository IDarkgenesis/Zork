#include "Player.h"
#include "Room.h"
#include "Item.h"
#include "Exit.h"

Player::Player(string Name, string Description, Room* Location, int HitPoints, int BaseDamage) :
	Creature(Name, Description, Location, HitPoints, BaseDamage)
{
	
}

void Player::Look() const
{
	Entity::Look();
	for (auto it : Inventory)
	{
		it.second->Look();
	}
}

bool Player::Go(const string& Direction)
{
	if (Location)
	{
		Exit* SelectedExit = Location->GetExit(Direction);
		if (!SelectedExit)
		{
			cout << "There is nowhere to go in that direction" << endl;
			return false;
		}
		if (!SelectedExit->IsExitLocked())
		{
			Room* NewLocation = SelectedExit->IsContainerRoom(Location) ? SelectedExit->GetLeadsToRoom() : SelectedExit->GetContainerRoom();
			Location->PlayerLeaves();
			NewLocation->PlayerEnters(this);
			Location = NewLocation;

			return true;
		}
		else
		{
			cout << "This exit is locked!" << endl;
		}
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
