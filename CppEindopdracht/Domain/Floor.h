#pragma once
#include "Room.h"


class Floor
{
public:
	Floor();
	Floor(std::default_random_engine& generator, int width, int height, int floorLevel, int dungeonDepth);
	~Floor();

	void print() const;
	Room* startRoom() const;
private:
	int width_;
	int height_;
	int floorLevel_;
	Room*** rooms_;
	Room* startRoom_;

	void setRandomEnd(std::default_random_engine& generator) const;
	void setRandomStart(std::default_random_engine& generator);
	void generateRooms(std::default_random_engine& generator, int dungeonDepth);
	void linkAdjacentRooms(std::default_random_engine& generator) const;
};

