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

	if (EquippedWeapon)
	{
		cout << "You have " + EquippedWeapon->GetName() + " equipped" << endl;
		EquippedWeapon->Look();
	}

	if (EquippedArmor)
	{
		cout << "You have " + EquippedArmor->GetName() + " equipped" << endl;
		EquippedArmor->Look();
	}

	if (Inventory.size() > 0)
	{
		cout << "You have the following items in your inventory:" << endl;
		for (auto it : Inventory)
		{
			it.second->Look();
		}
	}
	else
	{
		cout << "Your inventory is empty" << endl;
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

	Creature::RecieveDamage(Enemy, DamageRecieved);

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
