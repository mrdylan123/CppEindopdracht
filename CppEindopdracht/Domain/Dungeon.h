#pragma once
#include "Floor.h"
#include "Hero.h"


class Dungeon
{
public:
	Dungeon(int width, int height, int depth);
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

	/**
	 * \brief Describes the condition of the current room and the exits of that room
	 */
	void describeCurrentRoom() const;

	/**
	 * \brief Moves the hero into the room in the specified direction
	 * \param direction Direction to move towards
	 */
	void move(Direction direction);
private:
	int depth_;
	Floor** floors_;
	Hero hero_;
	Room* currentRoom_;
};

