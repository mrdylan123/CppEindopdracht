#pragma once
#include "Item.h"
class DefencePotion : public Item
{
public:
	DefencePotion();
	~DefencePotion();

	void use(Hero& h) override;
};

