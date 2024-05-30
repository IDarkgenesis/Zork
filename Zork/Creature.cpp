#include "Creature.h"
#include "Room.h"

Creature::Creature(string Name, string Description, EntityType Type, Room* Location, int HitPoints, int BaseDamage) :
	Entity(Name, Description, Type, Location)
{	
	this->Location = Location;
	CurrentTarget = NULL;
	this->HitPoints = HitPoints;
	this->BaseDamage = BaseDamage;
}

void Creature::Go(Room* NewLocation)
{
	Location->RemoveFromContainer(this);
	NewLocation->AddToContainer(this);
	Location = NewLocation;
}

void Creature::Attack(Creature* Target)
{
	if (Target->IsAlive())
	{
		Target->RecieveDamage(this, BaseDamage);
		CurrentTarget = Target;
	}
}

void Creature::Attack()
{
	if (CurrentTarget->IsAlive())
	{
		CurrentTarget->RecieveDamage(this, BaseDamage);
	}
}

void Creature::RecieveDamage(Creature* Enemy, int DamageRecieved)
{
}

bool Creature::IsAlive() const
{
	return HitPoints >= 0;
}

Room* Creature::GetCurrentLocation() const
{
	return Location;
}
