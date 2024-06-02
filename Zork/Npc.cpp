#include "Npc.h"
#include "World.h"
#include "Room.h"
#include "Exit.h"
#include "Player.h"
#include "Item.h"
#include<string>

Npc::Npc(string Name, string Description, Room* Location, bool Hostile, int HitPoints, int BaseDamage) : 
    Creature(Name, Description, Location, HitPoints, BaseDamage)
{
    CurrentTarget = nullptr;
    this->Hostile = Hostile;
    if(Location)
    {
        Location->AddNpc(this);
    }
}

void Npc::Look() const
{

    if (IsAlive())
    {
        Entity::Look();
        if (Hostile) 
        {
            cout << Name + " is looking at you fiercely" << endl;
        }
    }
    else
    {
        cout << "A " + Name + " corpse lies on the ground" << endl;
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
    if (IsAlive() && Location)
    {
        if (CurrentTarget && CurrentTarget->GetCurrentLocation() == Location && CurrentTarget->IsAlive())
        {
            Attack();
        }
        else if (Hostile && !CurrentTarget && Location->IsPlayerInRoom())
        {
            CurrentTarget = Location->GetPlayerInRoom();
            Attack();
        }
    }
}

void Npc::RecieveDamage(Creature* Enemy, int DamageRecieved)
{
    Creature::RecieveDamage(Enemy, DamageRecieved);

    if (Enemy)
    {
        CurrentTarget = Enemy;
        Hostile = true;


        if (IsAlive())
        {
            cout << Name + " has " + to_string(HitPoints) + " hitpoints" << endl;
        }
        else
        {
            cout << Name << " died" << endl;
            HandleDeath();
        }
    }
}
