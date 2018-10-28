#include <random>
#include "Enemy.h"


Enemy::Enemy() : Entity(new char[30]{ "monster" }, 0, 0, 0, 0, 0, 0, 0), numberOfAttacks_{0}
{

}


Enemy::~Enemy()
{
}
