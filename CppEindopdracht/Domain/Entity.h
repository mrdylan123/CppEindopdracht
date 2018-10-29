#pragma once
class Entity
{
public:
	Entity(char* name, int level, int healthPoints, int attack, int minDamage, int maxDamage, int defence);
	virtual ~Entity();
	Entity(const Entity& other) = delete;
	Entity(Entity&& other) noexcept = delete;
	Entity& operator=(const Entity& other) = delete;
	Entity& operator=(Entity&& other) noexcept = delete;

	char* name() const;
	int level() const;
	bool isDead() const;

	virtual void describeCondition() const;
	void attack(Entity& enemy);

protected:
	char* name_;
	int level_;
	int healthPoints_;
	int attackChance_;
	int minDamage_;
	int maxDamage_;
	int defenceChance_;
};

