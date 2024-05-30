#pragma once

#include <iostream>

using namespace std;

class Entity
{
public:
	Entity(string Name, string Description);

	virtual void Tick();

	virtual void Look() const;

	string GetName() const;

protected:
	string Name;

	string Description;
};

