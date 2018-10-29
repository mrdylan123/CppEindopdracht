#pragma once
#include "Item.h"
class ExperiencePotion : public Item
{
public:
	ExperiencePotion();
	~ExperiencePotion();

	void use(Hero& h) override;
};

