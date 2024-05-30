#pragma once

#include "Entity.h"

using namespace std;

class Exit;
class Player;

class Room : public Entity
{
public:
	Room(string Name, string Description);

	void Look() const override;

	bool IsPlayerInRoom();

	Player* GetPlayerInRoom();

	void PlayerEnters(Player* Player);

	void PlayerLeaves(Player* Player);

private:
	map<string, Exit*> Exits;

	Player* CurrentPlayer;
};

