#include "Player.h"
#include "Room.h"

Player::Player(string Name, string Description, Room* Location, int HitPoints, int BaseDamage) :
	Creature(Name, Description, EntityType::PLAYER, Location, HitPoints, BaseDamage)
{

}

void Player::Go(Room* NewLocation)
{
	Location->PlayerLeaves(this);
	NewLocation->PlayerEnters(this);

	Location = NewLocation;
}

void Player::Pick(Item* Item)
{
	AddToContainer((Entity*)Item);
}

void Player::Drop(Item* Item)
{
	RemoveFromContainer((Entity*)Item);
}

void Player::RecieveDamage(Creature* Enemy, int DamageRecieved)
{
	HitPoints -= DamageRecieved;
}
