#pragma once
class Entity
{
public:
	Entity(int level);
	~Entity();

protected:
	char name_[30];
	int level_;
	int healthpoints_;
	int experiencepoints_;
	int attack_;
	int defence_;
};

