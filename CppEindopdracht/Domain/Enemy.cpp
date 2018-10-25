#include <random>
#include "Enemy.h"


Enemy::Enemy(std::default_random_engine& generator, const int floorLevel) : Entity(new char[30]{ "monster" }, 0, 0, 0, 0, 0)
{
	const std::uniform_int_distribution<int> levelDistribution(1, 2);

	level_ = floorLevel * 2 + levelDistribution(generator);
}


Enemy::~Enemy()
{
}
