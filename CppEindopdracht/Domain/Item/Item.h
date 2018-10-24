#pragma once
#include "../Hero.h"

class Item
{
public:
	Item();
	~Item();

	void use(Hero& h);

protected:
	char name_[30];
	bool isConsumable;
};

