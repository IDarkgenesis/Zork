# Zorklike
Author: Bartomeu Perelló Comas
Link to [Github](https://github.com/IDarkgenesis/Zork) repository.

This is a simple version of the Zork video game.

## The Game

### Main features 

The game consists of several rooms connected by exits. Exits can be locked or unlocked, and some may require a certain Key to be unlocked.

There are also items which can be Keys, Containers, Weapons and Armor. Items can be picked up, dropped on the floor or put inside a container, armor and weapons can be equipped by NPC and the Player giving boosts to their defense and damage respectively.

The game also features NPC, they can be hostile or neutral and have the capability of tracking and following the Player.

### Approach to implementation 
#### Class structure


First of all I decided to change the proposed Class structure. I removed the Type enumeration from the Entity class. The reason behind this change, is that I feel that having a field that is used to know the class of a children, kinds of defeat the purpose of having the children class, if you want to work with Items, you should have an ItemContainer so you know that you are working with Items all the time.

I also removed the list of Entity pointers from the Entity class. I prefer that only those classes that need to store elements should have it, like Room, Creatures and Items.

Rooms have three separate containers, one for each type of element it can contain, Items, Exits and Npcs. Creatures like NPC or the Player have a container of items to represent its inventory, Items also have an item container, which is only allowed to use when the ItemType of the Item is a Container.

Containers will show their content and allow you to put or remove items once they are open.

#### Combat

The combat system is pretty simple, hostile enemies will attack the player whenever they are in the same room, in case there was an allied NPC that could engage in combat their target would change to the last Creature that attacked it.

There are three statistics that are involved in combat, healthpoints, attack damage and defense. The player or NPC can equip one armor and weapon at a time. When an NPC dies, it drops all of its items on the floor.

Each Creature has a set health and a base damage, if a Creature has a weapon equipped, it will deal the damage of the weapon instead of its base damage. 

For every five defense points the Creature has on its armor it will reduce the incoming damage by 1, so if one armor has 15 defense it would subtract at most 3 points of the incoming damage.

#### Map

The map is composed of rooms that are connected by exits, the map can be viewed as a graph, where rooms are the nodes and exits are the edges that connect two rooms. The movement is done in the four cardinal directions, north, east, west and south.

Exits can be locked and unlocked by the Player, exits can be set so they require a given item to perform those actions.

Creatures have an aggro distance, if the player is inside this range, the NPC will track and move towards the Player. The implementation of this feature is done using a Breadth First Search (BFS).

Rooms are treated as nodes and exits represent the edges of a graph. The path that the BFS looks for takes into account locked exits, so if there is a path to the player, it ensures it won’t go through locked exits.

## How to play
In order to finish the game either the Player reaches a specific room or the player dies during a run.

The game Ticks whenever the Player has input a command that has been executed correctly.

### Available commands
These are the available commands used to play the game.

  

- **Look** -> Gives information about the Player surroundings, also if there are items or NPC in the room.

  

- **Go {direction}** -> Tries to move the player to the specified cardinal direction.

  

- **{direction}** ->Tries to move the player to the specified cardinal direction.

  
  

- **Attack {objective}** -> Deals damage to the specified objective and sets it as the current target.

  

- **Attack** -> Attacks the current target.

  

- **Pick {item}** -> Looks for the specified item in the current room or inside a container in our inventory, and puts it inside our inventory.

  

- **Drop {item}** -> Looks for the specified item in our inventory including containers and leaves the specified item in the current room.

  

- **Inventory** -> Gives information of the player, like equipped items, and inventory

  

- **Put {item} {container}** -> Look for the specified item in our inventory or container and put it on the given container.

  

- **Put {item} “word” {container}** -> Look for the specified item in our inventory or container and put it on the given container.

  

- **Unlock {direction}** -> Tries to unlock the exit in the specified direction without any item.

  

- **Unlock {direction} {item}** -> Tries to unlock the exit in the specified direction with the given item.

  

- **Unlock {direction} “word” {item}** -> Tries to unlock the exit in the specified direction with the given item.

  

- **Lock {direction}** -> Tries to lock the exit in the specified direction without any item.

  

- **Unlock {direction} {item}** -> Tries to lock the exit in the specified direction with the given item.

  

- **Unlock {direction} “word” {item}** -> Tries to lock the exit in the specified direction with the given item.

  

- **Equip {item}** -> Tries to equip the specified item.

  

- **Unequip {“weapon” | “armor”}** -> Unequips either the weapon or the armor and stores the item in the Player inventory.

  

- **Open {container}** -> Opens the specified container.

  

- **Close {container}**-> Closes the specified container.

- **Exit** -> Close the game.

### A winning strategy

One winning strategy is to go east to the Prison and pick and equip the MineHat which is hidden inside the Bag, then rush to the Mines ignoring the Dog and pick and equip the Pickaxe. Then go back to Courtyard and then south to face the GuardChief, once dead, pick up the required key to open the exit to the forest and pick up and equip its items. Finally go to the GuardRoom, kill the GuardianSuperior first and then the Guardian, unlock the exit and take the east route.

## License
MIT License

Copyright (c) [2024] [Bartomeu Perelló Comas]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
