#include "Item.h"

Item::Item(char* name) : name_(name), isConsumable_{false}
{
}


Item::~Item()
{
	delete name_;
}

char* Item::name() const
{
	return name_;
}

bool Item::isConsumable() const
{
	return  isConsumable_;
}

void use(Hero& h){};