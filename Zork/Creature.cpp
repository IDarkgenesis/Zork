#include "Creature.h"
#include "Room.h"
#include "Item.h"
#include <string>

Creature::Creature(string Name, string Description, Room* Location, int HitPoints, int BaseDamage) :
	Entity(Name, Description)
{	
	this->Location = Location;
	CurrentTarget = nullptr;
	this->HitPoints = HitPoints;
	this->BaseDamage = BaseDamage;
	this->EquippedWeapon = nullptr;
	this->EquippedArmor = nullptr;
}

bool Creature::Go(const string& Direction)
{
	return false;
}

bool Creature::Attack(const string& Target)
{
	if (Location) 
	{
		Creature* TargetPointer = Location->GetCreature(Target);
		// Target exists in current room
		if (TargetPointer && TargetPointer->IsAlive())
		{
			int DamageDealt = EquippedWeapon ? EquippedWeapon->GetValue() : BaseDamage;

			cout << endl << Name << " attacks " + TargetPointer->GetName() + " for " + to_string(DamageDealt) + " damage" << endl;
			TargetPointer->RecieveDamage(this, DamageDealt);
			CurrentTarget = TargetPointer;
			return true;
		}
		else
		{
			cout << "Target is not valid" << endl;
		}
	}

	// Location should always be valid
	return false;
}

bool Creature::Attack()
{
	if (CurrentTarget && Location->GetCreature(CurrentTarget->GetName()) && CurrentTarget->IsAlive())
	{
		int DamageDealt = EquippedWeapon ? EquippedWeapon->GetValue() : BaseDamage;

		cout << endl << Name << " attacks " + CurrentTarget->GetName() + " for " + to_string(DamageDealt) + " damage" << endl;
		CurrentTarget->RecieveDamage(this, DamageDealt);
		return true;
	}

	cout << "Can't attack current target" << endl;
	return false;
}

bool Creature::Pick(const string& ItemName)
{
	// Check if item we want is in inventory or container
	auto FindItem = GetItemFromInventory(ItemName);
	if (FindItem.first)
	{
		// Item was found inside a container
		if (FindItem.second) {
			FindItem.second->RemoveItemFromContainer(FindItem.first);
			AddItemToInventory(FindItem.first);
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
		AddItemToInventory(FoundItem);
		Location->RemoveItem(FoundItem);
		cout << FoundItem->GetName() + " has been taken from the current room" << endl;
		return true;
	}

	cout << "Looks like " + ItemName + " is nowhere to be found here." << endl;
	return false;
}

bool Creature::Drop(const string& ItemName)
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
			RemoveItemFromInventory(FindItem.first);
			Location->AddItem(FindItem.first);
		}

		cout << ItemName + " has been dropped on the floor " << endl;
		return true;
	}

	cout << "Could not find " + ItemName + " in inventory to drop." << endl;
	return false;
}

bool Creature::EquipItem(const string& ItemName)
{
	auto FindItemToEquip = GetItemFromInventory(ItemName);
	if (!FindItemToEquip.first)
	{
		cout << "You don't have " + ItemName + " in the inventory." << endl;
		return false;
	}

	if (FindItemToEquip.first->GetItemType() != ItemType::Armor && FindItemToEquip.first->GetItemType() != ItemType::Weapon)
	{
		cout << ItemName + " is not a valid item to equip." << endl;
		return false;
	}

	Item* EquippedItem = (FindItemToEquip.first->GetItemType() == ItemType::Weapon) ? EquippedWeapon : EquippedArmor;
	if (EquippedItem)
	{
		cout << "You already have an item equipped in that slot. Unequip it first" << endl;
		return false;
	}
	
	// Equip the item
	if (FindItemToEquip.first->GetItemType() == ItemType::Weapon)
	{
		EquippedWeapon = FindItemToEquip.first;
	}
	else 
	{
		EquippedArmor = FindItemToEquip.first;
	}

	// Remove item from container
	if (FindItemToEquip.second)
	{
		FindItemToEquip.second->RemoveItemFromContainer(FindItemToEquip.first);
	}
	// Remove item from inventory
	else
	{
		RemoveItemFromInventory(FindItemToEquip.first);
	}
	cout << "You equipped " + ItemName << endl;
	return true;
}

bool Creature::UnequipItem(const string& ItemName)
{

	if (ItemName != "weapon" && ItemName != "armor")
	{
		cout << "Plase input a slot name, either weapon or armor" << endl;
		return false;
	}

	Item* UnequipedItem = (ItemName == "weapon") ? EquippedWeapon : EquippedArmor;
	if (UnequipedItem) 
	{
		AddItemToInventory(UnequipedItem);
		if (ItemName == "weapon")
		{
			EquippedWeapon = nullptr;
		}
		else 
		{
			EquippedArmor = nullptr;
		}

		cout << "You unequipped " + UnequipedItem->GetName() + " and stored it in the inventory." << endl;
		return true;
	}

	cout << "You don't have a " + ItemName + " to unequip." << endl;

	return false;
}

void Creature::AutoEquip(Item* EquipItem)
{
	if (!EquipItem)
	{
		return;
	}
	if (EquipItem->GetItemType() == ItemType::Weapon)
	{
		if (EquippedWeapon) 
		{
			AddItemToInventory(EquippedWeapon);
		}
		EquippedWeapon = EquipItem;
	}
	else if (EquipItem->GetItemType() == ItemType::Armor)
	{
		if (EquippedArmor) 
		{
			AddItemToInventory(EquippedArmor);
		}
		EquippedArmor = EquipItem;
	}
}

void Creature::RecieveDamage(Creature* Enemy, int DamageRecieved)
{

	int DamageMitigation = EquippedArmor ? (EquippedArmor->GetValue() / 5) : 0;
	int FinalRecievedDamage = max(DamageRecieved - DamageMitigation, 0);

	HitPoints -= FinalRecievedDamage;

	if (DamageMitigation > 0)
	{
		cout << Name + " has mitigated damage with its armor and recieved " + to_string(FinalRecievedDamage) << endl;
	}
}

bool Creature::IsAlive() const
{
	return HitPoints > 0;
}

bool Creature::HasTarget() const
{
	return CurrentTarget;
}

void Creature::HandleDeath()
{
	// Drop Inventory and current Items on the floor
	int DroppedItems = 0;
	if (EquippedWeapon)
	{
		Location->AddItem(EquippedWeapon);
		EquippedWeapon = nullptr;
		++DroppedItems;
	}

	if (EquippedArmor)
	{
		Location->AddItem(EquippedArmor);
		EquippedWeapon = nullptr;
		++DroppedItems;
	}

	for (auto it : Inventory)
	{
		Location->AddItem(it.second);
		++DroppedItems;
	}

	Inventory.clear();

	if (DroppedItems > 0)
	{
		cout << "It looks like " + Name + " dropped some items" << endl;
	}
}

Room* Creature::GetCurrentLocation() const
{
	return Location;
}

pair<Item*, Item*> Creature::GetItemFromInventory(const string& ItemName) const
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


bool Creature::AddItemToInventory(Item* NewItem)
{
	if (NewItem)
	{
		auto it = Inventory.find(NewItem->GetName());
		if (it == Inventory.cend())
		{
			Inventory.insert(pair<string, Item*>(NewItem->GetName(), NewItem));
		}
	}

	return false;
}

bool Creature::RemoveItemFromInventory(Item* OutItem)
{
	if (OutItem)
	{
		auto it = Inventory.find(OutItem->GetName());
		if (it != Inventory.cend())
		{
			Inventory.erase(it);
			return true;
		}
	}
	
	return false;
}


