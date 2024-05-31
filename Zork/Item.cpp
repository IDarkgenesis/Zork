#include "Item.h"

Item::Item(string Name, string Description, ItemType Type)
	: Entity(Name, Description)
{
	this->Type = Type;
}

void Item::Look() const
{
	Entity::Look();

	if (Type == ItemType::Container)
	{
		cout << "This is a container, and contains:" << endl;
		for (auto it : Container)
		{
			it.second->Look();
		}
	}
}

ItemType Item::GetItemType() const
{
	return Type;
}

bool Item::AddItemToContainer(Item* NewItem)
{
	// Check if new item to store is not itself and current type is a container
	if (NewItem && NewItem != this && Type == ItemType::Container)
	{
		auto it = Container.find(NewItem->GetName());

		if (it == Container.cend())
		{
			Container.insert(pair<string, Item*>(NewItem->GetName(), NewItem));
			return true;
		}
	}
	return false;
}

bool Item::RemoveItemFromContainer(Item* OutItem)
{
	if (OutItem && Type == ItemType::Container)
	{
		// Look if the item is in current container
		auto it = Container.find(OutItem->GetName());

		if (it != Container.cend())
		{
			Container.erase(it);
			cout << OutItem->GetName() + "has been removed from " + Name;
			return true;
		}

		// Check if this item is inside another Container of inventory
		for (auto CurrentItem : Container)
		{
			if (CurrentItem.second->RemoveItemFromContainer(OutItem))
			{
				cout << OutItem->GetName() + "has been removed from " + CurrentItem.second->GetName();
				return true;
			}
		}
	}
	return false;
}

Item* Item::GetItemFromContainer(const string& ItemName) const
{
	if(Type == ItemType::Container)
	{
		auto it = Container.find(ItemName);
		if (it != Container.cend())
		{
			return it->second;
		}
		// If not in current container check other containers

		for (auto CurrentItem : Container)
		{
			Item* ItemFound = CurrentItem.second->GetItemFromContainer(ItemName);
			if (ItemFound)
			{
				return ItemFound;
			}
		}
	}
	return nullptr;
}
