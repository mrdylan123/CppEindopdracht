#pragma once
#include "../Hero.h"

class Item
{
public:
	Item(char* name);
	virtual ~Item();

	char* name() const;
	bool isConsumable() const;

	virtual void use(Hero& h) = 0;

protected:
	char* name_;
	bool isConsumable_;
};

