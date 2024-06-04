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
	Room* GuardRoom = new Room("GuardRoom", "This is where guards rest when they are not keeping an eye on prisioners.");
	Room* Courtyard = new Room("Courtyard", "You can see the forest at a distance, if only you cold reach it, you would be free.");
	Room* PrisonGate = new Room("PrisonGate", "You are in front of the big prison gate, it's impossible to escape through this route");
	Room* Mines = new Room("Mines", "The dark and cold mines that you have to work on every day, you hate this place");
	Room* Forest = new Room("Forest", "Finally you are outside of the prison !");

	Item* GuardRoomKey = new Item("GuardRoomKey", "This key opens the metal door that connects the Prison with the GuardRoom", ItemType::Key);
	Courtyard->AddItem(GuardRoomKey);

	Item* GuardForestKey = new Item("GuardForestKey", "This key allows you to open the door at the Guard Room that leads to the Forest", ItemType::Key);

	Exit* CellPrisonExit = new Exit("east", "The cell door at your right looks like its open, thy must have forgot to close it.", "west", "Although its a bit dark you can still see your cell behind.", Cell, Prison);
	Exit* PrisonCourtyardExit = new Exit("south", "You can see the big wooden door that goes to the Courtyard at you south.", "north", "The big wooden door to the Prison is at your back", Prison, Courtyard);
	Exit* PrisonGaurdRoomExit = new Exit("east", "At your right there is the guard room", "west", "Going west would allow you to go back to the Prison", Prison, GuardRoom, GuardRoomKey);
	Exit* GaurdRoomForestExit = new Exit("east", "You feel fresh air comming form the east", "wast", "You can go back to the Guard Room if you go west", GuardRoom, Forest, GuardForestKey);
	Exit* CourtyardGaurdRoomExit = new Exit("east", "At your east you see the path that guards use to go to their office", "south", "You can go back to the courtyard if you go south", Courtyard, GuardRoom);
	Exit* CourtyardMinesExit = new Exit("west", "At your left there are the mines", "east", "You can go back to the courtyard if you go east", Courtyard, Mines);
	Exit* CourtyarPrisonGateExit = new Exit("south", "Going down you can see the big prison gate", "north", "North is the direction you should take if want to go back", Courtyard, PrisonGate);

	Npc* GuardChief = new Npc("GuardChief", "He is the leader of the guards, diligent at his job", PrisonGate, true, 15, 1, 0);
	Npc* GuardDog = new Npc("GuardDog", "A dog who is in charge of looking for fugitives", PrisonGate, true, 5, 3, 1);

	Npc* Guardian = new Npc("Guardian", "He has been resting on the guard room, waitng for his shift", GuardRoom, true, 8, 1, 0);
	Npc* Rat = new Npc("Rat", "A small rat, you see tons of them down below", Mines, false, 5, 1, 0);

	Item* Bag = new Item("Bag", "A cloth bag, usefull for carrying items", ItemType::Container);
	Prison->AddItem(Bag);

	Item* MineCap = new Item("MineCap", "You use it when you go to the mines, you only lack your pickaxe", ItemType::Armor, 5);
	Bag->AutoAddItem(MineCap);

	Item* Pickaxe = new Item("Pickaxe", "Your rusty and trusty pickaxe, it seems unbrekable", ItemType::Weapon, 5);
	Mines->AddItem(Pickaxe);
	
	Item* Dagger = new Item("Dagger", "A small but effetive weapon", ItemType::Weapon, 7);
	Item* Chainmail = new Item("Chainmail", "A proper armor, surely will protect you well from hits", ItemType::Armor, 10);
	Guardian->AutoEquip(Chainmail);
	Guardian->AutoEquip(Dagger);

	Item* Sword = new Item("Sword", "A sharp blade that will go through flesh without problems", ItemType::Weapon, 10);
	Item* MetalArmor = new Item("MetalArmor", "A metal and sturdy armor", ItemType::Armor, 15);
	GuardChief->AddItemToInventory(GuardForestKey);
	GuardChief->AutoEquip(Sword);
	GuardChief->AutoEquip(MetalArmor);

	Npc* GuardianSuperior = new Npc("GuardianSuperior", "He is the second in command of this prison, he likes to figth with his bare hands", GuardRoom, true, 10, 15, 0);

	AddToWorldEntities(GuardChief);
	AddToWorldEntities(GuardDog);
	AddToWorldEntities(Guardian);
	AddToWorldEntities(GuardianSuperior);
	AddToWorldEntities(Rat);

	WinningRoom = Forest;
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

		if (!CurrentPlayer->IsAlive() || CurrentPlayer->GetCurrentLocation() == WinningRoom)
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
		case GameCommand::Open:
			if (CommandTokens.size() == 2) return CurrentPlayer->OpenContainer(CommandTokens[1]);
			break;
		case GameCommand::Close:
			if (CommandTokens.size() == 2) return CurrentPlayer->CloseContainer(CommandTokens[1]);
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
	else if (CompareStrings(Token, "open")) return GameCommand::Open;
	else if (CompareStrings(Token, "close")) return GameCommand::Close;
	else if (CompareStrings(Token, "quit") || CompareStrings(Token, "exit")) return GameCommand::Quit;

	return GameCommand::NoCommand;
}

