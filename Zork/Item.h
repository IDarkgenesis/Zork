#pragma once

#include "Entity.h"
#include<map>

enum class ItemType
{
	Container,
	Key,
	Other
};

class Item : public Entity
{
public:
	Item(string Name, string Description, ItemType Type);

	void Look() const override;

	ItemType GetItemType() const;

	bool AddItemToContainer(Item* NewItem);
	bool RemoveItemFromContainer(Item* OutItem);
	Item* GetItemFromContainer(const string& ItemName) const;

private:

	ItemType Type;

	map<string, Item*> Container;
};

