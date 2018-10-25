#pragma once
#include <random>

class Item;
class Enemy;

class Room
{
public:
	Room();
	Room(std::default_random_engine& generator, int floorLevel, bool containsStairCaseUp, bool containsStairCaseDown);
	~Room();

	char* description();
	bool containsStairCaseUp() const;
	bool containsStairCaseDown() const;

	Room* northRoom() const;
	Room* eastRoom() const;
	Room* southRoom() const;
	Room* westRoom() const;

	void setNorthRoom(Room* room);
	void setEastRoom(Room* room);
	void setSouthRoom(Room* room);
	void setWestRoom(Room* room);

	void setEnd();
	void setStart();

	void setVisited();

	void print() const;
private:
	char description_[100];
	bool isVisited_;

	bool containsStairCaseUp_;
	bool containsStairCaseDown_;
	bool isStart_;
	bool isEnd_;

	Room* northRoom_;
	Room* eastRoom_;
	Room* southRoom_;
	Room* westRoom_;

	Enemy* enemy_;

	Item* item_;

	void setRandomDescription(std::default_random_engine& generator);
	void setRandomItem(std::default_random_engine& generator);
};

