#include "Creature.h"
#include "Room.h"
#include <string>

Creature::Creature(string Name, string Description, Room* Location, int HitPoints, int BaseDamage) :
	Entity(Name, Description)
{	
	this->Location = Location;
	CurrentTarget = NULL;
	this->HitPoints = HitPoints;
	this->BaseDamage = BaseDamage;
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
			cout << endl << Name << " attacks " + TargetPointer->GetName() + " for " + to_string(BaseDamage) + " damage" << endl;
			TargetPointer->RecieveDamage(this, BaseDamage);
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
		cout << endl << Name << " attacks " + CurrentTarget->GetName() + " for " + to_string(BaseDamage) + " damage" << endl;
		CurrentTarget->RecieveDamage(this, BaseDamage);
		return true;
	}

	cout << "Can't attack current target" << endl;
	return false;
}

void Creature::RecieveDamage(Creature* Enemy, int DamageRecieved)
{

}

bool Creature::IsAlive() const
{
	return HitPoints > 0;
}

bool Creature::HasTarget() const
{
	return CurrentTarget;
}

Room* Creature::GetCurrentLocation() const
{
	return Location;
}
