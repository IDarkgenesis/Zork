#include "Npc.h"
#include "World.h"
#include "Room.h"

Npc::Npc(string Name, string Description, Room* Location, bool Hostile, int HitPoints, int BaseDamage) : 
    Creature(Name, Description, Location, HitPoints, BaseDamage)
{
    CurrentTarget = NULL;
    this->Hostile = Hostile;
}

void Npc::Go(Room* NewLocation)
{
    NewLocation->AddNpc(this);
    Location->RemoveNpc(this);
    Location = NewLocation;
}

bool Npc::IsHostile() const
{
    return Hostile;
}

void Npc::Tick()
{
    if (Hostile)
    {
        if (CurrentTarget->GetCurrentLocation() == Location)
        {
            Attack();
        }
        else if (Location->IsPlayerInRoom())
        {
            CurrentTarget = (Creature*)Location->GetPlayerInRoom();
            Attack();
        }
    }
}

void Npc::RecieveDamage(Creature* Enemy, int DamageRecieved)
{
    CurrentTarget = Enemy;
    Hostile = true;
    HitPoints -= DamageRecieved;
}
