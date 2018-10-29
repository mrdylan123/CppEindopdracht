#include "HealthPotion.h"
#include <iostream>

HealthPotion::HealthPotion() : Item(new char[30]{ "Levenselixer" })
{
	isConsumable_ = true;
}


HealthPotion::~HealthPotion()
{
}

void HealthPotion::use(Hero& h)
{
	h.increaseHealthPoints(5);
	std::cout << "Je levenspunten zijn opgehoogd met 5!" << std::endl;
}
