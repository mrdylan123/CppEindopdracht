#include "Hero.h"
#include "Item/Item.h"
#include <iostream>
#include "Item/Sword.h"
#include "Item/Armor.h"


Hero::Hero() : Entity(new char[30]{ "Hero" }, 1, 5, 75, 1, 3, 10), equippedArmor_(nullptr), equippedSword_(nullptr),
	items_{ new Item*[10]{} },
	experiencePoints_(0)
{
}

Hero::Hero(char* name) : Entity(name, 1, 5, 75, 1, 3, 10), equippedArmor_(nullptr), equippedSword_(nullptr),
	items_{ new Item*[10]{} },
	experiencePoints_(0)
{
}


Hero::~Hero()
{
	if (items_ != nullptr)
	{
		for (int i = 0; i < 10; i++)
		{
			delete items_[i];
		}
		delete[] items_;
	}
}

void Hero::gainExperience(Entity& enemy)
{
	const int addedExperience = 50 + enemy.level() - level_;

	gainExperience(addedExperience);
}

void Hero::gainExperience(const int experience)
{
	experiencePoints_ += experience;

	std::cout << "Je verdiende " << experience << " xp-punten." << std::endl;

	if (experiencePoints_ >= 100)
	{
		// Hero leveled up
		level_++;
		experiencePoints_ -= 100;

		minDamage_ *= 2;
		maxDamage_ *= 2.5;

		defenceChance_ *= 1.5;

		if (defenceChance_ > 70)
			defenceChance_ = 70;

		attackChance_ *= 1.1;

		if (attackChance_ > 90)
			attackChance_ = 90;

		healthPoints_ += 15;

		std::cout << "Je bent nu level " << level_ << "!" << std::endl;
	}
}

void Hero::addItem(Item* item) const
{
	// Check if inventory is not already full
	if (items_[9] != nullptr)
	{
		std::cout << "Je inventaris zit vol!" << std::endl;
	}

	for (int i = 0; i < 10; i++)
	{
		if (items_[i] == nullptr)
		{
			items_[i] = item;

			std::cout << item->name() << " zit nu in je inventaris." << std::endl;

			break;
		}
	}
}

void Hero::useItem(const int index)
{
	if (items_[index] == nullptr)
		throw std::exception{ "Er is geen item in je inventaris op die plek." };


	items_[index]->use(*this);

	// Delete the item from memory when it is a consumable
	if (items_[index]->isConsumable())
	{
		delete items_[index];
		items_[index] = nullptr;
	}
}

void Hero::equipSword(Sword* sword)
{
	// Remove damage upgrade from current sword, if present
	if (equippedSword_ != nullptr)
		decreaseDamage(equippedSword_->damage());

	equippedSword_ = sword;

	increaseDamage(sword->damage());
}

void Hero::equipArmor(Armor* armor)
{
	// Remove defence upgrade from current armor, if present
	if (equippedArmor_ != nullptr)
		decreaseDefence(equippedArmor_->defence());

	equippedArmor_ = armor;

	increaseDefence(armor->defence());
}

void Hero::rest()
{
	std::cout << "Je rust uit en je levenspunten worden verhoogt met 1" << std::endl;
	healthPoints_ += 1;
}

void Hero::increaseDamage(const int damage)
{
	minDamage_ += damage;
	maxDamage_ += damage;
}

void Hero::decreaseDamage(const int damage)
{
	minDamage_ -= damage;
	maxDamage_ -= damage;
}

void Hero::increaseDefence(const int defence)
{
	defenceChance_ += defence;
}

void Hero::decreaseDefence(const int defence)
{
	defenceChance_ -= defence;
}

void Hero::increaseHealthPoints(const int healthPoints)
{
	healthPoints_ += healthPoints;
}

void Hero::printItems() const
{
	std::cout << "Items: ";

	for (int i = 0; i < 10; i++)
	{
		if (items_[i] == nullptr)
			continue;

		std::cout << "[" << i << "] " << items_[i]->name() << ", ";
	}

	std::cout << std::endl;
}

void Hero::describeCondition() const
{
	std::cout << "Naam: " << name_ << " Level: " << level_ << " Ervaringspunten: "
		<< experiencePoints_ << " Levenspunten: " << healthPoints_
		<< " Aanval: " << attackChance_ << " Verdediging: "
		<< defenceChance_ << " Minimale schade: " << minDamage_
		<< " Maximale schade: " << maxDamage_ << std::endl;
}
