#include "Floor.h"
#include "Room.h"
#include <iostream>
#include "../RandomGenerator.h"

Floor::Floor(const int width, const int height, const int floorLevel, const int dungeonDepth) :
	width_{ width },
	height_{ height },
	floorLevel_{ floorLevel }
{
	generateRooms(dungeonDepth);

	if (floorLevel_ == dungeonDepth - 1)
		setRandomEnd();

	if (floorLevel_ == 0)
		setRandomStart();

	linkAdjacentRooms();
}

Floor::~Floor()
{
	for (int x = 0; x < width_; x++) {
		// Delete the individual rooms in a row
		for (int y = 0; y < height_; y++) {
			delete rooms_[x][y];
		}

		// Delete the row array
		delete[] rooms_[x];
	}

	// Delete the columns array
	delete[] rooms_;
}

void Floor::setRandomEnd() const
{
	RandomGenerator* generator = RandomGenerator::instance();

	int endX = generator->randomNumber(0, width_ - 1);
	int endY = generator->randomNumber(0, height_ - 1);

	// Endroom cannot also be a staircase room
	while (rooms_[endX][endY]->containsStairCaseDown() && rooms_[endX][endY]->containsStairCaseUp())
	{
		endX = generator->randomNumber(0, width_ - 1);
		endY = generator->randomNumber(0, height_ - 1);
	}

	rooms_[endX][endY]->setEnd();
}

void Floor::setRandomStart()
{
	RandomGenerator* generator = RandomGenerator::instance();

	int startX = generator->randomNumber(0, width_ - 1);
	int startY = generator->randomNumber(0, height_ - 1);

	// Startroom cannot also be a staircase room
	while (rooms_[startX][startY]->containsStairCaseDown() && rooms_[startX][startY]->containsStairCaseUp())
	{
		startX = generator->randomNumber(0, width_ - 1);
		startY = generator->randomNumber(0, height_ - 1);
	}

	rooms_[startX][startY]->setStart();
	startRoom_ = rooms_[startX][startY];
}

void Floor::print() const
{
	for (int y = 0; y < height_; y++)
	{
		for (int x = 0; x < width_; x++)
		{
			rooms_[x][y]->print();
		}

		std::cout << std::endl;
	}
}

Room* Floor::startRoom() const
{
	return startRoom_;
}

Room* Floor::stairCaseUpRoom() const
{
	return stairCaseUpRoom_;
}

Room* Floor::stairCaseDownRoom() const
{
	return stairCaseDownRoom_;
}

void Floor::generateRooms(const int dungeonDepth)
{
	// Determine the location of the staircase upwards and downwards
	RandomGenerator* generator = RandomGenerator::instance();

	int stairCaseUpX = -1, stairCaseUpY = -1, stairCaseDownX = -1, stairCaseDownY = -1;

	// First floor does not have a staircase up
	if (floorLevel_ != 0)
	{
		stairCaseUpX = generator->randomNumber(0, width_ - 1);
		stairCaseUpY = generator->randomNumber(0, height_ - 1);
	}

	// Last floor does not have a staircase down
	if (floorLevel_ != dungeonDepth - 1)
	{
		stairCaseDownX = generator->randomNumber(0, width_ - 1);
		stairCaseDownY = generator->randomNumber(0, height_ - 1);
	}

	while (stairCaseUpX != -1 && stairCaseDownX != -1 && stairCaseUpX == stairCaseDownX && stairCaseUpY == stairCaseDownY)
	{
		stairCaseDownX = generator->randomNumber(0, width_ - 1);
		stairCaseDownY = generator->randomNumber(0, height_ - 1);
	}

	// Create a grid of rooms
	rooms_ = new Room**[width_];

	for (int i = 0; i < width_; i++) {
		rooms_[i] = new Room*[height_];
	}

	for (int y = 0; y < height_; y++)
	{
		for (int x = 0; x < width_; x++)
		{
			rooms_[x][y] = new Room{
				floorLevel_,
				x == stairCaseUpX && y == stairCaseUpY,
				x == stairCaseDownX && y == stairCaseDownY,
			};

			if (rooms_[x][y]->containsStairCaseDown())
				stairCaseDownRoom_ = rooms_[x][y];

			if (rooms_[x][y]->containsStairCaseUp())
				stairCaseUpRoom_ = rooms_[x][y];
		}
	}
}

void Floor::linkAdjacentRooms() const
{
	// Link rooms with adjacent rooms
	for (int y = 0; y < height_; y++)
	{
		for (int x = 0; x < width_; x++)
		{
			Room* room = rooms_[x][y];

			if (y - 1 >= 0)
				room->setNorthRoom(rooms_[x][y - 1]);

			if (y + 1 <= height_ - 1)
				room->setSouthRoom(rooms_[x][y + 1]);

			if (x - 1 >= 0)
				room->setWestRoom(rooms_[x - 1][y]);

			if (x + 1 <= width_ - 1)
				room->setEastRoom(rooms_[x + 1][y]);
		}
	}
}