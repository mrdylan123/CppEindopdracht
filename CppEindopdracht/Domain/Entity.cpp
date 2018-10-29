#include "Entity.h"
#include <iostream>
#include "../RandomGenerator.h"


Entity::Entity(char* name, const int level, const int healthPoints, const int attack, const int minDamage, const int maxDamage, const int defence) :
	name_{ name }, level_{ level }, healthPoints_{ healthPoints }, attackChance_{ attack }, minDamage_{ minDamage }, maxDamage_{ maxDamage }, defenceChance_{ defence }
{
}

Entity::~Entity()
{
	delete[] name_;
}

char* Entity::name() const
{
	return name_;
}

int Entity::level() const
{
	return level_;
}

bool Entity::isDead() const
{
	return healthPoints_ <= 0;
}

void Entity::describeCondition() const
{
	std::cout << "Naam: " << name_ << " Level: " << level_ << " Levenspunten: " << healthPoints_ << " Aanval: " << attackChance_ << " Verdediging: " << defenceChance_ << std::endl;
}

void Entity::attack(Entity& enemy)
{
	RandomGenerator* generator = RandomGenerator::instance();

	const int attack = generator->randomNumber(1, 100);

	if (attack <= attackChance_)
	{
		const int enemyDefence = generator->randomNumber(1, 100);

		if (enemyDefence >= enemy.defenceChance_)
		{
			const int damage = generator->randomNumber(minDamage_, maxDamage_);

			enemy.healthPoints_ -= damage;

			std::cout << name_ << " raakt de " << enemy.name_ << " voor " << damage << " schade." << std::endl;
		}
		else
		{
			std::cout << name_ << " probeerde aan te vallen, maar de " << enemy.name_ << " verdedigde de aanval." << std::endl;
		}
	}
	else
	{
		std::cout << name_ << " probeerde aan te vallen, maar de " << enemy.name_ << " werd niet geraakt." << std::endl;
	}
}
