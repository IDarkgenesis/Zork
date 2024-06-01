#include "Player.h"
#include "Room.h"
#include "Item.h"
#include "Exit.h"
#include <string>

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
	// Check if item we want is in inventory or container
	auto FindItem = GetItemFromInventory(ItemName);
	if (FindItem.first)
	{
		// Item was found inside a container
		if (FindItem.second) {
			FindItem.second->RemoveItemFromContainer(FindItem.first);
			Inventory.insert(pair<string, Item*>(FindItem.first->GetName(), FindItem.first));
			return true;
		}
		// Item already in our inventory
		else 
		{
			cout << ItemName + " is already in your inventory." << endl;
			return false;
		}
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

	cout << "Looks like " + ItemName + " is nowhere to be found here." << endl;
	return false;
}

bool Player::Drop(const string& ItemName)
{	
	// Check if item we want is in inventory or container
	auto FindItem = GetItemFromInventory(ItemName);
	if (FindItem.first) 
	{
		// Item is in a container
		if (FindItem.second)
		{
			FindItem.second->RemoveItemFromContainer(FindItem.first);
			Location->AddItem(FindItem.first);
		}
		// Item is in inventory
		else {
			auto it = Inventory.find(ItemName);
			Inventory.erase(it);
			Location->AddItem(FindItem.first);
		}

		cout << ItemName + " has been dropped on the floor " << endl;
		return true;
	}

	cout << "Could not find " + ItemName + " in inventory to drop." << endl;
	return false;
}

bool Player::Put(const string& ItemName, const string& Container)
{
	auto FindItem = GetItemFromInventory(ItemName);
	auto FindContainer = GetItemFromInventory(Container);

	// Check wheater item is somewhere in inventory and not already contained in desired container
	if (FindItem.first && FindContainer.first && FindItem.second != FindContainer.first) {
		
		if (FindItem.second)
		{
			FindItem.second->RemoveItemFromContainer(FindItem.first);
		}
		else 
		{
			auto it = Inventory.find(ItemName);
			Inventory.erase(it);
		}
		
		FindContainer.first->AddItemToContainer(FindItem.first);
		return true;
	}

	cout << "You cannot make that action" << endl;

	return false;
}

void Player::RecieveDamage(Creature* Enemy, int DamageRecieved)
{
	HitPoints -= DamageRecieved;

	if (IsAlive())
	{
		cout << "You have " + to_string(HitPoints) + " hitpoints" << endl;
	}
}

bool Player::UnlockDoor(const string& Direction, const string& Key)
{
	if (Location)
	{
		Exit* SelectedExit = Location->GetExit(Direction);

		if (!SelectedExit)
		{
			cout << "There is no exit in " + Direction << endl;
			return false;
		}
		else if (!SelectedExit->IsExitLocked())
		{
			cout << "This exit is already unlocked !" << endl;
			return false;
		}

		auto FoundKey = GetItemFromInventory(Key);
		if (SelectedExit->Unlock(FoundKey.first))
		{
			cout << "You unlocked " + Direction << endl;
			return true;
		}
		return false;
	}
	// Player location should always be valid
	cout << "An error with player Location happened" << endl;
	return false;
}

bool Player::LockDoor(const string& Direction, const string& Key)
{
	if (Location)
	{
		Exit* SelectedExit = Location->GetExit(Direction);
		if (!SelectedExit)
		{
			cout << "There is no exit in " + Direction << endl;
			return false;
		}
		else if (SelectedExit->IsExitLocked())
		{
			cout << "This exit is already locked !" << endl;
			return false;
		}

		auto FoundKey = GetItemFromInventory(Key);
		if (SelectedExit->Lock(FoundKey.first))
		{
			cout << "You locked " + Direction << endl;
			return true;
		}
		return false;
	}

	// Player location should always be valid
	cout << "An error with player Location happened" << endl;
	return false;
}

pair<Item*, Item*> Player::GetItemFromInventory(const string& ItemName) const
{
	pair<Item*, Item*> FoundItem = pair<Item*, Item*>(nullptr, nullptr);

	// Check if item is in inventory
	auto it = Inventory.find(ItemName);
	if (it != Inventory.cend()) {
		FoundItem.first = it->second;
	}

	// Look into containers for desired item
	if (!FoundItem.first) {
		pair<Item*, Item*> LookingItem;
		for (auto CurrentItem : Inventory)
		{
			LookingItem = CurrentItem.second->GetItemFromContainer(ItemName);
			if (LookingItem.first)
			{
				FoundItem.first = LookingItem.first;
				FoundItem.second = LookingItem.second;
				break;
			}

		}
	}
	return FoundItem;
}
