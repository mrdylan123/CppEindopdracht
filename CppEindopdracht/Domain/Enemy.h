#pragma once
#include "Entity.h"

class Enemy : public Entity
{
public:
	Enemy(std::default_random_engine& generator, int floorLevel);
	~Enemy();
};