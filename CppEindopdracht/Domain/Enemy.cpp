#include <random>
#include "Enemy.h"


Enemy::Enemy() : Entity(new char[30], 0, 0, 0, 0, 0, 0, 0), numberOfAttacks_{ 0 }
{
}


Enemy::~Enemy()
{
}

Enemy::Enemy(const Enemy& other) : Entity(new char[30], other.level_, other.healthPoints_,
	other.experiencePoints_, other.attack_, other.minDamage_, other.maxDamage_,
	other.defence_), numberOfAttacks_(0)
{
	std::memcpy(name_, other.name_, 30);
}

Enemy::Enemy(Enemy&& other) noexcept : Entity(other.name_, other.level_, other.healthPoints_,
	other.experiencePoints_, other.attack_, other.minDamage_,
	other.maxDamage_, other.defence_), numberOfAttacks_(0)
{
	other.name_ = nullptr;
}

Enemy& Enemy::operator=(const Enemy& other)
{
	if (this == &other)
		return *this;

	delete[] name_;

	name_ = new char[30];
	std::memcpy(name_, other.name_, 30);

	level_ = other.level_;
	healthPoints_ = other.healthPoints_;
	experiencePoints_ = other.experiencePoints_;
	attack_ = other.attack_;
	minDamage_ = other.minDamage_;
	maxDamage_ = other.maxDamage_;
	defence_ = other.defence_;

	return *this;
}

Enemy& Enemy::operator=(Enemy&& other) noexcept
{
	if (this == &other)
		return *this;

	name_ = other.name_;
	other.name_ = nullptr;

	level_ = other.level_;
	healthPoints_ = other.healthPoints_;
	experiencePoints_ = other.experiencePoints_;
	attack_ = other.attack_;
	minDamage_ = other.minDamage_;
	maxDamage_ = other.maxDamage_;
	defence_ = other.defence_;

	return *this;
}
