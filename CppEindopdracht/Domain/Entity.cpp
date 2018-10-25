#include "Entity.h"


Entity::Entity(char* name, const int level, const int healthPoints, const int experiencePoints, const int attack, const int defence) :
	name_{ name }, level_{ level }, healthPoints_{ healthPoints }, experiencePoints_{ experiencePoints }, attack_{ attack }, defence_{ defence }
{
}

Entity::~Entity()
{
	delete[] name_;
}
