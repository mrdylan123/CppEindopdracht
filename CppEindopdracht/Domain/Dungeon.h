#pragma once
#include "Floor.h"
#include "Hero.h"


class Dungeon
{
public:
	Dungeon(int width, int height, int depth);
	~Dungeon();

	enum Direction { North, East, South, West};

	void showMap() const;
	void describeCurrentRoom() const;
	void move(Direction direction);
private:
	int depth_;
	Floor** floors_;
	Hero hero_;
	Room* currentRoom_;
};

