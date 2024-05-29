#include "Entity.h"

Entity::Entity(string Name, string Description, EntityType Type, Entity* Partent)
{
	this->Name = Name;
	this->Description = Description;
	this->Type = Type;
	this->Parent = Partent;

	if (Partent) 
	{
		Partent->AddToContainer(this);
	}
}

void Entity::Tick()
{
	cout << Name + ": I am ticking" << endl;
}

void Entity::Look() const
{

	cout << Name << endl << Description << endl;
}

void Entity::AddToContainer(Entity* Child)
{
	auto iterator = Container.find(Child->Name);

	if (iterator != Container.cend())
	{
		cout << Child->Name + " is already in " + Name << endl;
		return;
	}
	
	Container.insert(pair<string, Entity*>(Child->Name, Child));
}

void Entity::RemoveFromContainer(Entity* Child)
{
	auto iterator = Container.find(Child->Name);

	if (iterator == Container.cend())
	{
		cout << Child->Name + " not in " + Name << endl;
		return;
	}

	Container.erase(iterator);
}

string Entity::GetName() const
{
	return Name;
}
