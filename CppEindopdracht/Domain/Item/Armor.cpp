#include "Armor.h"
#include "../../RandomGenerator.h"
#include <iostream>

Armor::Armor(const int floorLevel) : Item(new char[100]{ "Uitrusting - " })
{
	RandomGenerator* generator = RandomGenerator::instance();

	defence_ = generator->randomNumber(10, 20) + floorLevel;

	char defenceString[32];
	sprintf_s(defenceString, "%d", defence_);

	strcat_s(name_, 100, defenceString);
}


Armor::~Armor()
{
}

int Armor::defence() const
{
	return defence_;
}

void Armor::use(Hero& hero)
{
	hero.equipArmor(this);
	std::cout << "Je bent nu uitgerust met een " << name_ << "." << std::endl;
}
