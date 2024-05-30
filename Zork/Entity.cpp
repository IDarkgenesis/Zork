#include "Entity.h"

Entity::Entity(string Name, string Description)
{
	this->Name = Name;
	this->Description = Description;
}

void Entity::Tick()
{
	cout << Name + ": I am ticking" << endl;
}

void Entity::Look() const
{

	cout << Name << endl << Description << endl;
}

string Entity::GetName() const
{
	return Name;
}
