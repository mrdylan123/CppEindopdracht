#include "Dungeon.h"
#include <ctime>
#include <random>
#include <iostream>

Dungeon::Dungeon(const int width, const int height, const int depth) : depth_{ depth }, hero_{ Hero{} }
{
	std::default_random_engine generator;
	generator.seed(time(nullptr));

	floors_ = new Floor*[depth_];

	for (int i = 0; i < depth; i++)
	{
		floors_[i] = new Floor{ generator, width, height, i, depth_ };
	}

	currentRoom_ = floors_[0]->startRoom();
	currentRoom_->setVisited();
}


Dungeon::~Dungeon()
{
	for (int i = 0; i < depth_; i++) {
		delete floors_[i];
	}
	delete[] floors_;
}

void Dungeon::showMap() const
{
	floors_[0]->print();
}

void Dungeon::describeCurrentRoom() const
{
	std::cout << currentRoom_->description() << std::endl << std::endl;

	std::cout << "Uitgangen: ";

	if (currentRoom_->northRoom() != nullptr)
		std::cout << "noord ";

	if (currentRoom_->eastRoom() != nullptr)
		std::cout << "oost ";

	if (currentRoom_->southRoom() != nullptr)
		std::cout << "zuid ";

	if (currentRoom_->westRoom() != nullptr)
		std::cout << "west ";

	std::cout << std::endl << std::endl;
}

void Dungeon::move(const Direction direction)
{
	Room* nextRoom = nullptr;

	switch (direction)
	{
	case North: nextRoom = currentRoom_->northRoom(); break;
	case East: nextRoom = currentRoom_->eastRoom(); break;
	case South: nextRoom = currentRoom_->southRoom(); break;
	case West: nextRoom = currentRoom_->westRoom(); break;
	}

	if (nextRoom == nullptr)
		throw std::exception{ "Kan niet die richting op gaan." };

	currentRoom_ = nextRoom;
	describeCurrentRoom();
}
