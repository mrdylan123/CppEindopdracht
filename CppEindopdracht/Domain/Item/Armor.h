#pragma once
#include "Item.h"
class Armor : public Item
{
public:
	Armor();
	~Armor();

private:
	int defence_;
};

