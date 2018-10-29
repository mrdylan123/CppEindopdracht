#include "DefencePotion.h"
#include <ostream>
#include <iostream>


DefencePotion::DefencePotion() : Item(new char[30]{ "Verdedigings elixer" })
{
	isConsumable_ = true;
}


DefencePotion::~DefencePotion()
{
}

void DefencePotion::use(Hero& h)
{
	h.increaseDefence(5);
	std::cout << "Je verdediging is opgehoogd met 5!" << std::endl;
}
