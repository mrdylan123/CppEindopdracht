#include "Hero.h"
#include "Item/Item.h"


Hero::Hero() : Entity(new char[5]{ "Hero" }, 1, 5, 0, 1, 1, 3, 1), items_{ new Item[50] }
{
}


Hero::~Hero()
{
	delete[] items_;
}

Hero::Hero(Hero&& other) noexcept : Entity(other.name_, other.level_, other.healthPoints_,
	other.experiencePoints_, other.attack_, other.minDamage_,
	other.maxDamage_, other.defence_), items_(other.items_)
{
	other.name_ = nullptr;
	other.items_ = nullptr;
}

Hero& Hero::operator=(Hero&& other) noexcept
{
	if (this == &other)
		return *this;

	name_ = other.name_;
	other.name_ = nullptr;

	items_ = other.items_;
	other.items_ = nullptr;

	level_ = other.level_;
	healthPoints_ = other.healthPoints_;
	experiencePoints_ = other.experiencePoints_;
	attack_ = other.attack_;
	minDamage_ = other.minDamage_;
	maxDamage_ = other.maxDamage_;
	defence_ = other.defence_;

	return *this;
}
