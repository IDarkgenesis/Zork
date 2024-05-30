#include "World.h"
#include "Entity.h"
#include "Player.h"
#include "Room.h"

World::World()
{
	Room* Courtyard = new Room("Courtyard", "You see beatueful white fences.");

	WorldEntities.insert(pair<string, Entity*>(Courtyard->GetName(), Courtyard));

	this->CurrentPlayer = new Player("Player", "A player", Courtyard);
}

void World::Tick(const vector<string>& CommandTokens)
{
	if (ExecutePlayerCommand(CommandTokens))
	{
		for (auto entity : WorldEntities)
		{
			entity.second->Tick();
		}
	}
	else {
		cout << "Command not recognized" << endl;
	}
}

bool World::IsGameOver() const
{
	return bGameOver;
}

void World::SetGameOver(bool GameOver)
{
	bGameOver = GameOver;
}

bool World::ExecutePlayerCommand(const vector<string>& CommandTokens)
{
	// TESTING GAME OVER FUNCTION AND TICK IS WORKING
	switch (CommandTokens.size())
	{
	case 1:
		return true;
	case 2:
		bGameOver = true;
		return true;
	default:
		return false;
	}
}

void World::AddToWorldEntities(Entity* NewEntity)
{
	auto iterator = WorldEntities.find(NewEntity->GetName());

	if (iterator != WorldEntities.cend())
	{
		return;
	}

	WorldEntities.insert(pair<string, Entity*>(NewEntity->GetName(), NewEntity));
}
