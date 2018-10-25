#include "Floor.h"
#include "Room.h"
#include <iostream>

Floor::Floor()
{
}

Floor::Floor(std::default_random_engine& generator, const int width, const int height, const int floorLevel, const int dungeonDepth) :
	width_{ width },
	height_{ height },
	floorLevel_{ floorLevel }
{
	generateRooms(generator, dungeonDepth);

	if (floorLevel_ == dungeonDepth - 1)
		setRandomEnd(generator);

	if (floorLevel_ == 0)
		setRandomStart(generator);
	
	linkAdjacentRooms(generator);
	// TODO: Set a random room from a floor with an enemy to a BOSS enemy, Start location, Stairs down and Stairs up.
}

Floor::~Floor()
{
	for (int y = 0; y < height_; y++) {
		// Delete the individual rooms in a row
		for (int x = 0; x < width_; x++) {
			delete rooms_[y][x];
		}

		// Delete the row array
		delete[] rooms_[y];
	}

	// Delete the columns array
	delete[] rooms_;
}

void Floor::setRandomEnd(std::default_random_engine& generator) const
{
	const std::uniform_int_distribution<int> xDistribution(0, width_ - 1);
	const std::uniform_int_distribution<int> yDistribution(0, height_ - 1);

	int endX = xDistribution(generator);
	int endY = yDistribution(generator);

	while (rooms_[endX][endY]->containsStairCaseDown() && rooms_[endX][endY]->containsStairCaseUp())
	{
		endX = xDistribution(generator);
		endY = yDistribution(generator);
	}

	rooms_[endX][endY]->setEnd();
}

void Floor::setRandomStart(std::default_random_engine& generator)
{
	const std::uniform_int_distribution<int> xDistribution(0, width_ - 1);
	const std::uniform_int_distribution<int> yDistribution(0, height_ - 1);

	int startX = xDistribution(generator);
	int endY = yDistribution(generator);

	while (rooms_[startX][endY]->containsStairCaseDown() && rooms_[startX][endY]->containsStairCaseUp())
	{
		startX = xDistribution(generator);
		endY = yDistribution(generator);
	}

	rooms_[startX][endY]->setStart();
	startRoom_ = rooms_[startX][endY];
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

void Floor::generateRooms(std::default_random_engine& generator, const int dungeonDepth)
{
	// Determine the location of the staircase upwards and downwards
	const std::uniform_int_distribution<int> xDistribution(0, width_ - 1);
	const std::uniform_int_distribution<int> yDistribution(0, height_ - 1);

	int stairCaseUpX = -1, stairCaseUpY = -1, stairCaseDownX = -1, stairCaseDownY = -1;

	if (floorLevel_ != 0)
	{
		stairCaseUpX = xDistribution(generator);
		stairCaseUpY = yDistribution(generator);
	}
	
	if (floorLevel_ != dungeonDepth - 1)
	{
		stairCaseDownX = xDistribution(generator);
		stairCaseDownY = yDistribution(generator);
	}

	while (stairCaseUpX != -1 && stairCaseDownX != -1 && stairCaseUpX == stairCaseDownX && stairCaseUpY == stairCaseDownY)
	{
		stairCaseDownX = xDistribution(generator);
		stairCaseDownY = yDistribution(generator);
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
				generator,
				y,
				x == stairCaseUpX && y == stairCaseUpY,
				x == stairCaseDownX && y == stairCaseDownY
			};
		}
	}
}

void Floor::linkAdjacentRooms(std::default_random_engine& generator) const
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