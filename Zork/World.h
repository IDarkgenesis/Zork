#pragma once

#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Entity;
class Player;

enum class GameCommand
{
	Look,
	Go,
	Attack,
	Pick,
	Drop,
	Inventory,
	Put,
	Lock,
	Unlock,
	Quit,
	NoCommand
};

class World
{
public:
	World();

	void Tick(const vector<string>& CommandTokens );

	bool IsGameOver() const;

	void SetGameOver(bool GameOver);

private:
	map<string, class Entity*> WorldEntities;

	bool bGameOver = false;

	bool ExecutePlayerCommand(const vector<string>& CommandTokens);

	void AddToWorldEntities(Entity* NewEntity);

	Player* CurrentPlayer;

	bool CompareStrings(string IncommingString, string ExpectedString);

	GameCommand TokenToCommand(string Token);
};

