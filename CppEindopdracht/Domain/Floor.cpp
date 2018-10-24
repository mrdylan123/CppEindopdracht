#include "Floor.h"
#include "Room.h"
#include <iostream>
#include "Enemy.h"


Floor::Floor()
{
}

Floor::Floor(std::default_random_engine& generator, const int width, const int height)
{
	rooms_ = new Room**[width];

	for (int i = 0; i < width; i++) {
		rooms_[i] = new Room*[height];
	}

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			rooms_[x][y] = new Room{ generator, y };
		}
	}

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			Room* room = rooms_[x][y];

			if (y - 1 > 0)
				room->setNorthRoom(rooms_[x][y - 1]);

			if (y + 1 < height - 1)
				room->setSouthRoom(rooms_[x][y + 1]);

			if (x - 1 > 0)
				room->setWestRoom(rooms_[x - 1][y]);

			if (x + 1 < width - 1)
				room->setEastRoom(rooms_[x + 1][y]);
		}
	}

	// TODO: Set a random room from a floor with an enemy to a BOSS enemy, Start location, Stairs down and Stairs up.
}

Floor::~Floor()
{
	for (int i = 0; i < 10; i++) {
		delete[] rooms_[i];
	}
	delete[] rooms_;
}
