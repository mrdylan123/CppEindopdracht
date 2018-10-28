#pragma once
#include "Room.h"


class Floor
{
public:
	Floor(int width, int height, int floorLevel, int dungeonDepth);
	~Floor();
	Floor(const Floor& other) = delete;
	Floor(Floor&& other) noexcept = delete;
	Floor& operator=(const Floor& other) = delete;
	Floor& operator=(Floor&& other) noexcept = delete;

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

