#pragma once
#include "Domain/Enemy.h"

class EnemyFactory
{
public:
	static EnemyFactory *s_instance;

	EnemyFactory();
	~EnemyFactory();

	static EnemyFactory *instance();

	Enemy* GetRandomEnemy(int floorLevel);

private:
	Enemy* enemies_;
};

