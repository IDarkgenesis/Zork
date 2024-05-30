#pragma once

#include "Entity.h"

class Room;

class Creature : public Entity
{
public:
	Creature(string Name, string Description, Room* Location, int HitPoints, int BaseDamage);

	virtual void Go(Room* Location);

	void Attack(Creature* Target);
	void Attack();

	virtual void RecieveDamage(Creature* Enemy, int DamageRecieved);

	bool IsAlive() const;

	Room* GetCurrentLocation() const;

protected:
	Room* Location;
	
	int HitPoints;

	int BaseDamage;

	Creature* CurrentTarget;
};

