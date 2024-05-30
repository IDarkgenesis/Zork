// Zork.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <sstream>
#include <vector>

#include "World.h"

using namespace std;

vector<string> Tokenize(const string& command, char separator)
{
    vector<string> Tokens;
    string NewToken = "";
    for (char CurrentCharacter : command)
    {
        if (CurrentCharacter != separator && CurrentCharacter != '\t')
        {
            NewToken += CurrentCharacter;
        }
        else if(NewToken.size() > 0)
        {
            Tokens.push_back(NewToken);
            NewToken = "";
        }
    }

    if(NewToken.size() > 0) Tokens.push_back(NewToken);
    
    return Tokens;
}

int main()
{

    cout << "Welcome to Zork!" << endl << endl;
    
    // Create game world
    World NewWorld = World();
    cout << endl;

    // Get player input
    string PlayerInput;

    // Loop while not Game over or player input
    while (!NewWorld.IsGameOver() && getline(cin, PlayerInput))
    {
        vector<string> Tokens = Tokenize(PlayerInput, ' ');

        NewWorld.Tick(Tokens);
        cout << endl;
    }

    cout << "Thanks for playing" << endl;
}
