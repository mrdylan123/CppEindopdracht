#include "Dungeon.h"
#include <ctime>
#include <random>

Dungeon::Dungeon(const int width, const int height)
{
	std::default_random_engine generator;
	generator.seed(time(0));

	floors_ = new Floor*[5];

	for (int i = 0; i < 5; i++)
	{
		floors_[i] = new Floor{ generator, width, height };
	}
}


Dungeon::~Dungeon()
{
	for (int i = 0; i < 5; i++) {
		delete floors_[i];
	}
	delete[] floors_;
}
