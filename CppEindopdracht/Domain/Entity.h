#pragma once
class Entity
{
public:
	Entity(char* name, int level, int healthPoints, int experiencePoints, int attack, int minDamage, int maxDamage, int defence);
	~Entity();
	Entity(const Entity& other) = delete;
	Entity(Entity&& other) noexcept = delete;
	Entity& operator=(const Entity& other) = delete;
	Entity& operator=(Entity&& other) noexcept = delete;

protected:
	char* name_;
	int level_;
	int healthPoints_;
	int experiencePoints_;
	int attack_;
	int minDamage_;
	int maxDamage_;
	int defence_;
};

