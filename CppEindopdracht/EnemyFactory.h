#pragma once
#include "Domain/Enemy.h"

class EnemyFactory
{
public:
	static EnemyFactory* s_instance;

	~EnemyFactory();
	EnemyFactory(const EnemyFactory& other) = delete;
	EnemyFactory(EnemyFactory&& other) noexcept = delete;
	EnemyFactory& operator=(const EnemyFactory& other) = delete;
	EnemyFactory& operator=(EnemyFactory&& other) noexcept = delete;

	static EnemyFactory* instance();

	Enemy* getRandomEnemy(int floorLevel, int dungeonDepth) const;
	Enemy* getRandomBoss() const;

private:
	EnemyFactory();
	Enemy* enemies_;
};

