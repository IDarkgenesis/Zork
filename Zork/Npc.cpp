#include "Npc.h"
#include "World.h"
#include "Room.h"
#include "Exit.h"
#include "Player.h"
#include "Item.h"
#include<string>
#include<set>
#include<queue>

Npc::Npc(string Name, string Description, Room* Location, bool Hostile, int HitPoints, int BaseDamage, int AggroDistance) :
    Creature(Name, Description, Location, HitPoints, BaseDamage)
{
    CurrentTarget = nullptr;
    this->Hostile = Hostile;
    this->AggroDistance = AggroDistance;
    if(Location)
    {
        Location->AddNpc(this);
        
    }
    HomeRoom = Location;
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
            
            if (Location->IsPlayerInRoom())
            {
                cout << Name + " moves " + Direction << endl;
            }
            
            Location->RemoveNpc(this);
            NewLocation->AddNpc(this);

            Location = NewLocation;

            if (Location->IsPlayerInRoom())
            {
                cout << Name + " moved in" << endl;
            }
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
        else if(Hostile)
        {
            string direction = TrackPlayerInRange();
            if (direction != "None")
            {
                Go(direction);
            }
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

string Npc::TrackPlayerInRange()
{
    set<string> VisitedRooms;
    // First -> Child room, Second -> Parent Room
    map<string, string> Path;
    string RoomOfTarget = "None";

    queue<Room*> Queue;
    Queue.push(Location);

    while (!Queue.empty())
    {
        Room* CurrentRoom = Queue.front();
        
        Queue.pop();

        // Check if current Room is not visited
        auto VisitedRoomIterator = VisitedRooms.find(CurrentRoom->GetName());
        if (VisitedRoomIterator == VisitedRooms.cend())
        {
            VisitedRooms.insert(CurrentRoom->GetName());

            // If player in room -> Push current room and break loop
            if (CurrentRoom->IsPlayerInRoom()) 
            {
                RoomOfTarget = CurrentRoom->GetName();
                break;
            }
            // If player not in room -> Kepp looking in nex rooms
            else
            {
                for (auto exit : CurrentRoom->GetExitList())
                {
                    if(!exit.second->IsExitLocked())
                    {
                        Room* NextRoom = exit.second->IsContainerRoom(CurrentRoom) ? exit.second->GetLeadsToRoom() : exit.second->GetContainerRoom();
                        // Add adjacent rooms if not already visited
                        VisitedRoomIterator = VisitedRooms.find(NextRoom->GetName());
                        if (VisitedRoomIterator == VisitedRooms.cend())
                        {
                            Queue.push(NextRoom);
                            Path.insert(pair<string, string>(NextRoom->GetName(), CurrentRoom->GetName()));
                        }
                    }
                }
            }
        }
    }

    if (RoomOfTarget == "None")
    {
        return "None";
    }

    // Reconstruct path to player;
    string NextRoomName = RoomOfTarget;
    string PreviousRoomName = "None";
    int DistanceToPlayer = 0;
    while (NextRoomName != Location->GetName())
    {
        PreviousRoomName = NextRoomName;
        NextRoomName = Path.find(NextRoomName)->second;
        ++DistanceToPlayer;
    }

    if (DistanceToPlayer > AggroDistance)
    {
        return "None";
    }

    for (auto CurrentExit : Location->GetExitList())
    {
        if (CurrentExit.second->GetContainerRoom()->GetName() == PreviousRoomName) 
        {
            return CurrentExit.second->GetReversePathName();
        }
        else if (CurrentExit.second->GetLeadsToRoom()->GetName() == PreviousRoomName)
        {
            return CurrentExit.second->GetName();
        }
    }

    return "None";
}
