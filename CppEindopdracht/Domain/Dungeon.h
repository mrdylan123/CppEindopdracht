#pragma once
#include "Floor.h"
#include "Hero.h"


class Dungeon
{
public:
	Dungeon(int width, int height, int depth, Hero* hero);
	~Dungeon();
	Dungeon(const Dungeon& other) = delete;
	Dungeon(Dungeon&& other) noexcept = delete;
	Dungeon& operator=(const Dungeon& other) = delete;
	Dungeon& operator=(Dungeon&& other) noexcept = delete;

	enum Direction { North, East, South, West};

	/**
	 * \brief Prints the layout of the current floor in the console
	 */
	void showMap() const;

	void showItems() const;

	/**
	 * \brief Describes the condition of the current room and the exits of that room
	 */
	void enter() const;

	/**
	 * \brief Moves the hero into the room in the specified direction
	 * \param direction Direction to move towards
	 */
	void move(Direction direction);

	void flee();
	void fight();
	void attack();
	void pickUpItem() const;
	void useStaircase();
	void rest() const;

	bool gameOver() const;
	Hero* hero() const;
private:
	int depth_;
	Floor** floors_;
	Hero* hero_;
	Room* currentRoom_;
	bool inCombat_;
	bool fleeing_;
	bool gameOver_;

	void nextRoom(Direction direction);
};

