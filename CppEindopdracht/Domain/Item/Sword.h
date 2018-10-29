#pragma once
#include "Item.h"

class Sword : public Item
{
public:
	Sword(int floorLevel);
	~Sword();

	int damage() const;

	void use(Hero& hero) override;
private:
	int damage_;
};

