#include "Room.h"
#include "Player.h"

Room::Room(string Name, string Description) : Entity(Name, Description, EntityType::ROOM)
{
	CurrentPlayer = nullptr;
}

void Room::Look() const
{
	cout << Name + ": " << Description << endl;

	for (auto CurrentElement : Container)
	{
		CurrentElement.second->GetName();
	}
}

bool Room::IsPlayerInRoom()
{
	return Container.find("Player") != Container.cend();
}

Player* Room::GetPlayerInRoom()
{
	return CurrentPlayer;
}

void Room::PlayerEnters(Player* NewPlayer)
{
	CurrentPlayer = NewPlayer;
	AddToContainer(NewPlayer);
}

void Room::PlayerLeaves(Player* OldPlayer)
{
	CurrentPlayer = nullptr;
	RemoveFromContainer(OldPlayer);
}

