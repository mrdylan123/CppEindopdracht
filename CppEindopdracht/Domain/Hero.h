#pragma once
#include "Entity.h"

class Item;

class Hero : public Entity
{
public:
	Hero();
	~Hero();

	Hero(const Hero& other) = delete;
	Hero(Hero&& other) noexcept;
	Hero& operator=(const Hero& other) = delete;
	Hero& operator=(Hero&& other) noexcept;

private:
	Item* items_;

};



