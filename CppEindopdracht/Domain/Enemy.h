#pragma once
#include "Entity.h"

class EnemyFactory;

class Enemy : public Entity
{
public:
	Enemy();
	~Enemy();
	Enemy(const Enemy& other);
	Enemy(Enemy&& other) noexcept;
	Enemy& operator=(const Enemy& other);
	Enemy& operator=(Enemy&& other) noexcept;

	friend EnemyFactory;

private:
	int numberOfAttacks_;
};