#include "Item.h"
#include<string>

Item::Item(string Name, string Description, ItemType Type, int Value)
	: Entity(Name, Description)
{
	this->Type = Type;
	this->Value = Value;
	OpenedContainer = false;
}

void Item::Look() const
{
	cout << Name + ": " + Description;

	if (Type == ItemType::Container && Container.size() > 0 && OpenedContainer)
	{
		cout << endl << "--- Items inside " + Name + " ---" << endl;
		for (auto it : Container)
		{
			it.second->Look();
		}
		cout << "--- End of items of " + Name + " ---" << endl;
	}
	else if (Type == ItemType::Weapon)
	{
		cout << ", deals " + to_string(Value) + " damage";
	}
	else if (Type == ItemType::Armor) 
	{
		cout << ", has " + to_string(Value) + " defence";
	}

	cout << endl;
}

ItemType Item::GetItemType() const
{
	return Type;
}

int Item::GetValue() const
{
	return Value;
}

bool Item::AddItemToContainer(Item* NewItem)
{
	if (NewItem && Type == ItemType::Container) {

		if (!OpenedContainer)
		{
			cout << "Container " + Name + " is not opened" << endl;
			return false;
		}

		auto ContainsThis = NewItem->GetItemFromContainer(Name);
		if (!ContainsThis.first)
		{
			auto it = Container.find(NewItem->GetName());
			if (it == Container.cend())
			{
				Container.insert(pair<string, Item*>(NewItem->GetName(),NewItem));
				cout << NewItem->GetName() + " has been added to " + Name << endl;
				return true;
			}
		}
	}
	return false;
}

bool Item::RemoveItemFromContainer(Item* OutItem)
{
	if (OutItem && Type == ItemType::Container)
	{

		if (!OpenedContainer)
		{
			cout << "Container " + Name + " is not opened" << endl;
			return false;
		}

		pair<Item*, Item*> FoundItem = GetItemFromContainer(OutItem->GetName());
		if (FoundItem.first) 
		{
			// Check if container is not self (avoid infinite loop)
			if (FoundItem.second != this)
			{
				FoundItem.second->RemoveItemFromContainer(FoundItem.first);	
			}
			else
			{
				auto it = Container.find(OutItem->GetName());
				Container.erase(it);
			}
			cout << FoundItem.first->GetName() + " has been removed from " + FoundItem.second->GetName() << endl;
			return true;
		}
	}
	return false;
}

pair<Item*, Item*> Item::GetItemFromContainer(const string& ItemName)
{
	pair<Item*, Item*> FoundItem = pair<Item*, Item*>(nullptr, nullptr);

	if(Type == ItemType::Container)
	{
		if (!OpenedContainer)
		{
			cout << "Container " + Name + " is not opened, can't look if the item is inside" << endl;
			return FoundItem;
		}

		auto it = Container.find(ItemName);
		if (it != Container.cend())
		{
			FoundItem.first = it->second;
			FoundItem.second = this;
		}
		// Look into containers for desired item
		if (!FoundItem.first)
		{
			for (auto CurrentItem : Container)
			{
				pair<Item*, Item*> LookingItemContainer = CurrentItem.second->GetItemFromContainer(ItemName);
				if (LookingItemContainer.first)
				{
					FoundItem.first = LookingItemContainer.first;
					FoundItem.second = LookingItemContainer.second;
					break;
				}
			}
		}
	}
	return FoundItem;
}

void Item::AutoAddItem(Item* NewItem)
{
	auto FindItem = Container.find(NewItem->Name);

	if (FindItem == Container.cend())
	{
		Container.insert(pair<string, Item*>(NewItem->GetName(), NewItem));
	}
	
}

bool Item::OpenContainer()
{
	
	if (Type != ItemType::Container)
	{
		return false;
	}

	if (OpenedContainer)
	{
		cout << Name + " is already oppened" << endl;
		return false;
	}
	
	cout << "You opened " + Name << endl;
	OpenedContainer = true;
	return true;
}

bool Item::CloseContainer()
{
	if (Type != ItemType::Container)
	{
		return false;
	}

	if (!OpenedContainer)
	{
		cout << Name + " is already closed" << endl;
		return false;
	}

	cout << "You closed " + Name << endl;
	OpenedContainer = false;
	return true;
}
