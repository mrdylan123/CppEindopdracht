#pragma once
#include "Entity.h"

class HeroLoader;
class Item;
class Armor;
class Sword;

class Hero : public Entity
{
public:
	Hero();
	Hero(char* name);
	~Hero();

	Hero(const Hero& other) = default;
	Hero(Hero&& other) noexcept = default;
	Hero& operator=(const Hero& other) = default;
	Hero& operator=(Hero&& other) noexcept = default;

	friend HeroLoader;

	void gainExperience(Entity& enemy);
	void gainExperience(int experience);

	void addItem(Item* item) const;
	void useItem(int index);
	void equipSword(Sword* sword);
	void equipArmor(Armor* armor);

	void rest();

	void increaseDamage(int damage);
	void decreaseDamage(int damage);

	void increaseDefence(int defence);
	void decreaseDefence(int defence);

	void increaseHealthPoints(int healthPoints);

	void printItems() const;

	void describeCondition() const override;
private:
	Armor* equippedArmor_;
	Sword* equippedSword_;
	Item** items_;
	int experiencePoints_;

};



