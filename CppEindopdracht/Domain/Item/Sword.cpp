#include "Sword.h"
#include "../../RandomGenerator.h"
#include <iostream>

Sword::Sword(const int floorLevel) : Item(new char[100]{ "Zwaard - " })
{
	RandomGenerator* generator = RandomGenerator::instance();

	damage_ = generator->randomNumber(5, 10) + floorLevel;

	char damageString[32];
	sprintf_s(damageString, "%d", damage_);

	strcat_s(name_, 100, damageString);
}


Sword::~Sword()
{
}

int Sword::damage() const
{
	return damage_;
}

void Sword::use(Hero& hero)
{
	hero.equipSword(this);
	std::cout << "Je bent nu uitgerust met een " << name_ << "." << std::endl;
}
