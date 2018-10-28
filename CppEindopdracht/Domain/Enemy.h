#pragma once
#include "Entity.h"

class EnemyFactory;

class Enemy : public Entity
{
public:
	Enemy();
	~Enemy();

	friend EnemyFactory;

private:
	int numberOfAttacks_;
};