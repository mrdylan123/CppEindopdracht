#pragma once
#include <random>

class Item;
class Enemy;

class Room
{
public:
	Room();
	Room(std::default_random_engine& generator, int floorLevel);
	~Room();

	char* description();

	void setNorthRoom(Room* room);
	void setEastRoom(Room* room);
	void setSouthRoom(Room* room);
	void setWestRoom(Room* room);

private:
	char description_[100];
	bool isVisited_;

	Room* northRoom_;
	Room* eastRoom_;
	Room* southRoom_;
	Room* westRoom_;

	Enemy* enemy_;

	Item* item_;

	Item* getRandomItem(std::default_random_engine& generator);
};

