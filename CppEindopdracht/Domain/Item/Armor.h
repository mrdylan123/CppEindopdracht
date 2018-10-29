#pragma once
#include "Item.h"
class Armor : public Item
{
public:
	Armor(int floorLevel);
	~Armor();

	int defence() const;

	void use(Hero& hero) override;
private:
	int defence_;
};

