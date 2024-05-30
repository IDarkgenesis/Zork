#include "Npc.h"
#include "World.h"
#include "Room.h"

Npc::Npc(string Name, string Description, Room* Location, bool Hostile, int HitPoints, int BaseDamage) : 
    Creature(Name, Description, Location, HitPoints, BaseDamage)
{
    CurrentTarget = NULL;
    this->Hostile = Hostile;
}

bool Npc::Go(Room* NewLocation)
{
    if (Location && NewLocation)
    {
        Location->RemoveNpc(this);
        NewLocation->AddNpc(this);
        Location = NewLocation;
        return true;
    }

    return false;
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
