#pragma once
#include "Room.h"


class Floor
{
public:
	Floor();
	Floor(int width, int height, int floorLevel, int dungeonDepth);
	~Floor();

	void print() const;
	Room* startRoom() const;
private:
	int width_;
	int height_;
	int floorLevel_;
	Room*** rooms_;
	Room* startRoom_;

	void setRandomEnd() const;
	void setRandomStart();
	void generateRooms(int dungeonDepth);
	void linkAdjacentRooms() const;
};

