#pragma once
#include "Item.h"
class HealthPotion : public Item
{
public:
	HealthPotion();
	~HealthPotion();

	void use(Hero& h) override;
};

