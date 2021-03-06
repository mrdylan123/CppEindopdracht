#pragma once
#include <random>

class Item;
class Enemy;

class Room
{
public:
	Room(int floorLevel, bool containsStairCaseUp, bool containsStairCaseDown);
	~Room();
	Room(const Room& other) = delete;
	Room(Room&& other) noexcept = delete;
	Room& operator=(const Room& other) = delete;
	Room& operator=(Room&& other) noexcept = delete;

	char* description();
	bool containsStairCaseUp() const;
	bool containsStairCaseDown() const;

	Room* northRoom() const;
	Room* eastRoom() const;
	Room* southRoom() const;
	Room* westRoom() const;
	Enemy* enemy() const;
	bool isEnd() const;

	char* enemyName() const;
	int floorLevel() const;
	Item* item() const;

	Item* pickUpItem();

	void setNorthRoom(Room* room);
	void setEastRoom(Room* room);
	void setSouthRoom(Room* room);
	void setWestRoom(Room* room);

	void setEnd();
	void setStart();

	void setVisited();

	void describe() const;
	void enter(int dungeonDepth);
	void clear();

	void print() const;
private:
	char description_[100];
	bool isVisited_;

	int floorLevel_;
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

	void setRandomDescription();
	void setRandomItem();
};

