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

	cout << "You have the following items in your inventory:" << endl;
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

bool Player::Pick(const string& ItemName)
{
	// Check if the item we want to pick is already in our inventory
	auto it = Inventory.find(ItemName);

	if (it != Inventory.cend())
	{
		cout << ItemName + "Is already in you inventory !" << endl;
		return false;
	}

	// Check if item is in current room
	Item* FoundItem = Location->GetItem(ItemName);
	if (FoundItem)
	{
		Inventory.insert(pair<string, Item*>(FoundItem->GetName(), FoundItem));
		Location->RemoveItem(FoundItem);
		cout << FoundItem->GetName() + " has been taken from the current room" << endl;
		return true;
	}

	// Check if item is in a container in inventory
	for (auto CurrentItem : Inventory)
	{
		FoundItem = CurrentItem.second->GetItemFromContainer(ItemName);
		if (FoundItem) 
		{
			Inventory.insert(pair<string, Item*>(FoundItem->GetName(), FoundItem));
			CurrentItem.second->RemoveItemFromContainer(FoundItem);
			cout << "and put in your inventory" << endl;
			return true;
		}
	}

	cout << "Looks like " + ItemName + " is nowhere to be found here." << endl;
	return false;
}

bool Player::Drop(const string& ItemName)
{	
	// Check if the item we want to drop is at our inventory
	auto it = Inventory.find(ItemName);

	if (it != Inventory.cend())
	{
		Location->AddItem(it->second);
		Inventory.erase(it);
		cout << "You dropped " + ItemName + " on the floor." << endl;
		return true;
	}

	// Check if the item we want to drop is in a container
	Item* FoundItem = nullptr;
	for (auto CurrentItem : Inventory)
	{
		FoundItem = CurrentItem.second->GetItemFromContainer(ItemName);
		if (FoundItem)
		{
			Location->AddItem(FoundItem);
			CurrentItem.second->RemoveItemFromContainer(FoundItem);
			cout << "You dropped " + ItemName + " on the floor." << endl;
			return true;
		}
	}
	cout << "Could not find " + ItemName + " in inventory to drop." << endl;
	return false;
}

void Player::RecieveDamage(Creature* Enemy, int DamageRecieved)
{
	HitPoints -= DamageRecieved;
}
