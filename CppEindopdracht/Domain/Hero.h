#pragma once
#include "Entity.h"

class Item;

class Hero : public Entity
{
public:
	Hero();
	~Hero();

private:
	Item* items_;

};



