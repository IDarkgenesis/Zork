#include "World.h"
#include "Entity.h"
#include "Player.h"
#include "Room.h"
#include "Exit.h"
#include "Item.h"
#include "Npc.h"

World::World()
{ 
	Room* Cell = new Room("Cell", "You have been in this disgusting cell for weeks.");
	Room* Prison = new Room("Prison", "You have walked through this hallway everytime you are punished with force labor.");
	Exit* CellPrisonExit = new Exit("east", "The cell door at your right looks like its open, thy must have forgot to close it.", "west", "Although its a bit dark you can still see your cell behind.", Cell, Prison);

	Room* Courtyard = new Room("Courtyard", "Finally some fresh air, its a bit cold out here");
	Npc* Goblin = new Npc("Goblin", "A green and vile creature", Prison, true, 10, 1);

	Item* PrisonCourtKey = new Item("PrisonCourtKey", "This key opens the wooden door that connects the Prison with the Courtyard", ItemType::Key);
	Prison->AddItem(PrisonCourtKey);

	Item* Bag = new Item("Bag", "Is a small bag, lucky you!", ItemType::Container);
	Cell->AddItem(Bag);

	Item* Toolbox = new Item("Toolbox", "A toolbox, you can store things to it!", ItemType::Container);
	Prison->AddItem(Toolbox);

	Exit* PrisonCourtyardExit = new Exit("south","You can see the big wooden door that goes to the Courtyard at you south.", "north", "The big wooden door to the Prison is at your back", Prison, Courtyard, PrisonCourtKey);

	Item* Sword = new Item("Sword", "A sharp sword", ItemType::Weapon, 5);
	Item* Chainamail = new Item("Chainamail", "A trustworthy armor", ItemType::Armor, 15);
	Item* Leathercap = new Item("Leathercap", "A lether cap", ItemType::Armor, 5);

	Cell->AddItem(Sword);
	Cell->AddItem(Chainamail);
	Goblin->AutoEquip(Leathercap);

	AddToWorldEntities(Cell);
	AddToWorldEntities(Prison);
	AddToWorldEntities(Courtyard);
	AddToWorldEntities(Goblin);
	AddToWorldEntities(PrisonCourtKey);
	AddToWorldEntities(Bag);
	AddToWorldEntities(Toolbox);
	AddToWorldEntities(Sword);
	AddToWorldEntities(Chainamail);
	AddToWorldEntities(Leathercap);

	CurrentPlayer = new Player("Player", "A player", Cell, 100, 2);
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

		if (!CurrentPlayer->IsAlive())
		{
			bGameOver = true;
		}
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
			break;
		case GameCommand::Attack:
			if (CommandTokens.size() == 1) return CurrentPlayer->Attack();
			else if (CommandTokens.size() == 2) return CurrentPlayer->Attack(CommandTokens[1]);
			break;
		case GameCommand::Pick:
			if(CommandTokens.size() == 2) return CurrentPlayer->Pick(CommandTokens[1]);
			break;
		case GameCommand::Drop:
			if (CommandTokens.size() == 2) return CurrentPlayer->Drop(CommandTokens[1]);
			break;
		case GameCommand::Inventory:
			CurrentPlayer->Look();
			return true;
		case GameCommand::Put:
			if (CommandTokens.size() == 3) return CurrentPlayer->Put(CommandTokens[1], CommandTokens[2]);
			else if (CommandTokens.size() == 4)  return CurrentPlayer->Put(CommandTokens[1], CommandTokens[3]);
			break;
		case GameCommand::Unlock:
			if (CommandTokens.size() == 2) return CurrentPlayer->UnlockDoor(CommandTokens[1], "Nothing");
			else if (CommandTokens.size() == 3) return CurrentPlayer->UnlockDoor(CommandTokens[1], CommandTokens[2]);
			else if (CommandTokens.size() == 4)  return CurrentPlayer->UnlockDoor(CommandTokens[1], CommandTokens[3]);
			break;
		case GameCommand::Lock:
			if (CommandTokens.size() == 2) return CurrentPlayer->LockDoor(CommandTokens[1], "Nothing");
			else if (CommandTokens.size() == 3) return CurrentPlayer->LockDoor(CommandTokens[1], CommandTokens[2]);
			else if (CommandTokens.size() == 4)  return CurrentPlayer->LockDoor(CommandTokens[1], CommandTokens[3]);
			break;
		case GameCommand::Equip:
			if (CommandTokens.size() == 2) return CurrentPlayer->EquipItem(CommandTokens[1]);
			break;
		case GameCommand::Unequip:
			if (CommandTokens.size() == 2) return CurrentPlayer->UnequipItem(CommandTokens[1]);
			break;
		case GameCommand::Quit:
			bGameOver = true;
			return true;
		default:
			cout << "Command is not valid." << endl;
			return false;
		}
	}
	cout << "Command is not valid." << endl;
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
	else if (CompareStrings(Token, "pick")) return GameCommand::Pick;
	else if (CompareStrings(Token, "drop")) return GameCommand::Drop;
	else if (CompareStrings(Token, "put")) return GameCommand::Put;
	else if (CompareStrings(Token, "inventory")) return GameCommand::Inventory;
	else if (CompareStrings(Token, "unlock")) return GameCommand::Unlock;
	else if (CompareStrings(Token, "lock")) return GameCommand::Lock;
	else if (CompareStrings(Token, "equip")) return GameCommand::Equip;
	else if (CompareStrings(Token, "unequip")) return GameCommand::Unequip;
	else if (CompareStrings(Token, "quit") || CompareStrings(Token, "exit")) return GameCommand::Quit;

	return GameCommand::NoCommand;
}

