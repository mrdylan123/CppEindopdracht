#include "ExperiencePotion.h"

ExperiencePotion::ExperiencePotion() : Item(new char[30]{ "Ervarings punten elixer" })
{
	isConsumable_ = true;
}


ExperiencePotion::~ExperiencePotion()
{
}

void ExperiencePotion::use(Hero& h)
{
	h.gainExperience(25);
}
