#include "World.h"
#include "Entity.h"
#include "Player.h"
#include "Room.h"
#include "Exit.h"

World::World()
{ 
	Room* Cell = new Room("Cell", "You have been in this disgusting cell for weeks.");
	Room* Prison = new Room("Prison", "You have walked through this hallway everytime you are punished with force labor.");
	Exit* CellPrisonExit = new Exit("east", "The cell door at your right looks like its open, thy must have forgot to close it.", "west", "Although its a bit dark you can still see your cell behind", Cell, Prison);


	WorldEntities.insert(pair<string, Entity*>(Cell->GetName(), Cell));


	CurrentPlayer = new Player("Player", "A player", Cell);
	Cell->PlayerEnters(CurrentPlayer);

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
	if (CommandTokens.size() > 0)
	{
		GameCommand command = TokenToCommand(CommandTokens[0]);
		switch (command)
		{
		case GameCommand::Look:
			if (CommandTokens.size() > 1) CurrentPlayer->Look();
			else CurrentPlayer->GetCurrentLocation()->Look();
			return true;
		case GameCommand::Go:
			if (CommandTokens.size() > 1) return CurrentPlayer->Go(CommandTokens[1]);
			else  return CurrentPlayer->Go(CommandTokens[0]);
		case GameCommand::Unlock:
			break;
		case GameCommand::Attack:
			break;
		case GameCommand::Quit:
			bGameOver = true;
			return true;
		default:
			return false;
		}
	}

	return false;
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

bool World::CompareStrings(string IncommingString, string ExpectedString)
{
	// Convert Incomming string to lowerCase
	for (auto& currentChar : IncommingString)
	{
		currentChar = tolower(currentChar);
	}

	return IncommingString == ExpectedString;
}

GameCommand World::TokenToCommand(string Token)
{
	if (CompareStrings(Token, "look")) return GameCommand::Look;
	else if (CompareStrings(Token, "go") || CompareStrings(Token, "north") || CompareStrings(Token, "east") || CompareStrings(Token, "west") || CompareStrings(Token, "south")) return GameCommand::Go;
	else if (CompareStrings(Token, "unlock")) return GameCommand::Unlock;
	else if (CompareStrings(Token, "attack")) return GameCommand::Attack;
	else if (CompareStrings(Token, "quit")) return GameCommand::Quit;

	return GameCommand::NoCommand;
}

