#include "Hero.h"
#include "Item/Item.h"


Hero::Hero() : Entity(new char[5]{ "Hero" }, 1, 5, 0, 1, 1)
{
	items_ = new Item[50];
}


Hero::~Hero()
{
	delete[] items_;
}
