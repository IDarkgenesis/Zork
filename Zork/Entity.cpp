#include "Entity.h"

Entity::Entity(string Name, string Description)
{
	this->Name = Name;
	this->Description = Description;
}

void Entity::Tick()
{

}

void Entity::Look() const
{

	cout << Name + ": " << Description << endl;
}

string Entity::GetName() const
{
	return Name;
}
