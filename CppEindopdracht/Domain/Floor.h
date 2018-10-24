#pragma once
#include "Room.h"


class Floor
{
public:
	Floor();
	Floor(std::default_random_engine& generator, int width, int height);
	~Floor();

private:
	Room*** rooms_;
};

