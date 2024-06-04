#pragma once

#include "Entity.h"
#include<map>

enum class ItemType
{
	Container,
	Key,
	Weapon,
	Armor,
	Other
};

class Item : public Entity
{
public:
	Item(string Name, string Description, ItemType Type, int Value = 0);

	void Look() const override;

	ItemType GetItemType() const;
	int GetValue() const;

	bool AddItemToContainer(Item* NewItem);
	bool RemoveItemFromContainer(Item* OutItem);
	pair<Item*, Item*> GetItemFromContainer(const string& ItemName);
	void AutoAddItem(Item* NewItem);

	bool OpenContainer();
	bool CloseContainer();

private:

	ItemType Type;

	map<string, Item*> Container;

	int Value;

	bool OpenedContainer;
};

