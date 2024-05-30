#pragma once

#include "Creature.h"

class Npc : public Creature
{
public:
	Npc(string name, string Description, Room* Location, bool Hostile, int HitPoints = 1, int BaseDamage = 1);

	void Go(Room* Location) override;

	bool IsHostile() const;

	void Tick() override;

	void RecieveDamage(Creature* Enemy, int DamageRecieved) override;

private:

	bool Hostile;
};

