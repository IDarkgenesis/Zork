#include "Item.h"

Item::Item(string Name, string Description, ItemType Type)
	: Entity(Name, Description)
{
	this->Type = Type;
}

ItemType Item::GetItemType() const
{
	return Type;
}

bool Item::AddItemToContainer(Item* NewItem)
{
	if (NewItem && Type == ItemType::Container)
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
		auto it = Container.find(OutItem->GetName());

		if (it != Container.cend())
		{
			Container.erase(it);
			return true;
		}
	}
	return false;
}
