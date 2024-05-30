#include "Npc.h"
#include "World.h"
#include "Room.h"
#include "Exit.h"

Npc::Npc(string Name, string Description, Room* Location, bool Hostile, int HitPoints, int BaseDamage) : 
    Creature(Name, Description, Location, HitPoints, BaseDamage)
{
    CurrentTarget = NULL;
    this->Hostile = Hostile;
}

void Npc::Look() const
{
    Entity::Look();
    if (Hostile) {
        cout << "This creature is looking at you fiercely" << endl;
    }
}

bool Npc::Go(const string& Direction)
{
    if (!IsAlive()) return false;

    if (Location)
    {
        Exit* SelectedExit = Location->GetExit(Direction);
        if (!SelectedExit)
        {
            return false;
        }
        if (!SelectedExit->IsExitLocked())
        {
            Room* NewLocation = SelectedExit->IsContainerRoom(Location) ? SelectedExit->GetLeadsToRoom() : SelectedExit->GetContainerRoom();
            Location->RemoveNpc(this);
            NewLocation->AddNpc(this);

            if (Location->IsPlayerInRoom())
            {
                cout << Name + " is moving " + Direction << endl;
            }

            Location = NewLocation;
        }
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
        if (CurrentTarget && CurrentTarget->GetCurrentLocation() == Location)
        {
            Attack();
        }
        else if (Location && Location->IsPlayerInRoom())
        {
            CurrentTarget = (Creature*)Location->GetPlayerInRoom();
            Attack();
        }
    }
}

void Npc::RecieveDamage(Creature* Enemy, int DamageRecieved)
{
    if (Enemy)
    {
        CurrentTarget = Enemy;
        Hostile = true;
        HitPoints -= DamageRecieved;
    }
}
