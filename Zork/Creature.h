#pragma once

#include "Entity.h"
#include<vector>

class Room;

class Creature : public Entity
{
public:
	Creature(string Name, string Description, Room* Location, int HitPoints, int BaseDamage);

	virtual bool Go(const string& Direction);

	bool Attack(const string& Target);
	bool Attack();

	virtual void RecieveDamage(Creature* Enemy, int DamageRecieved);

	bool IsAlive() const;
	bool HasTarget() const;

	Room* GetCurrentLocation() const;

protected:
	Room* Location;
	
	int HitPoints;

	int BaseDamage;

	Creature* CurrentTarget;
};

