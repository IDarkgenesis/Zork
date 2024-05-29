#include "World.h"
#include "Entity.h"

World::World()
{
    Entity* Room = new Entity("Bakcyard", "You are at a backyard, you can se a beatufeful forest and white fences", EntityType::ROOM);
    Entity* Pep = new Entity("Pep", "This is pep, a human", EntityType::PLAYER, Room);

	AddToWorldEntities(Room);
	AddToWorldEntities(Pep);
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
