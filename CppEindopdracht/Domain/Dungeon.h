#pragma once
#include "Floor.h"


class Dungeon
{
public:
	Dungeon(int width, int height);
	~Dungeon();
private:
	Floor** floors_;
};

