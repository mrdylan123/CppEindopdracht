#include "Room.h"
#include <random>
#include <ctime>
#include "Enemy.h"
#include "Item/Armor.h"
#include "Item/Sword.h"
#include "Item/HealthPotion.h"
#include "Item/ExperiencePotion.h"
#include "Item/HolyGrenade.h"
#include <iostream>


Room::Room()
{
}

Room::Room(std::default_random_engine& generator, const int floorLevel, const bool containsStairCaseUp, const bool containsStairCaseDown) :
	isVisited_{ false },
	containsStairCaseUp_{ containsStairCaseUp },
	containsStairCaseDown_{ containsStairCaseDown }
{
	setRandomDescription(generator);
	setRandomItem(generator);

	const std::uniform_int_distribution<int> distribution(1, 3);

	// Generate a possible enemy, 1/3 chance
	if (distribution(generator) == 1)
	{
		enemy_ = new Enemy{ generator, floorLevel };
	}
	else
	{
		enemy_ = nullptr;
	}
}


Room::~Room()
{
	delete item_;
	delete enemy_;
}

char* Room::description()
{
	return description_;
}

bool Room::containsStairCaseUp() const
{
	return containsStairCaseUp_;
}

bool Room::containsStairCaseDown() const
{
	return containsStairCaseDown_;
}

Room* Room::northRoom() const
{
	return northRoom_;
}

Room* Room::eastRoom() const
{
	return eastRoom_;
}

Room* Room::southRoom() const
{
	return southRoom_;
}

Room* Room::westRoom() const
{
	return westRoom_;
}

void Room::setNorthRoom(Room* room)
{
	northRoom_ = room;
}

void Room::setEastRoom(Room* room)
{
	eastRoom_ = room;
}

void Room::setSouthRoom(Room* room)
{
	southRoom_ = room;
}

void Room::setWestRoom(Room* room)
{
	westRoom_ = room;
}

void Room::setEnd()
{
	isEnd_ = true;
}

void Room::setStart()
{
	isStart_ = true;
}

void Room::setVisited()
{
	isVisited_ = true;
}

void Room::print() const
{
	if (isStart_)
	{
		std::cout << "S";
		return;
	}

	if (!isVisited_)
	{
		std::cout << ".";
		return;
	}

	if (isEnd_)
	{
		std::cout << "E";
		return;
	}

	if (containsStairCaseUp_)
	{
		std::cout << "H";
		return;
	}

	if (containsStairCaseDown_)
	{
		std::cout << "L";
		return;
	}

	std::cout << "N";
}

void Room::setRandomDescription(std::default_random_engine& generator)
{
	const std::uniform_int_distribution<int> distribution(1, 3);

	// Generate description
	char size[15];
	char cleanliness[15];
	char object[35];

	char sizes[3][15] = { "kleine", "gemiddelde", "grote" };
	char cleanlinesses[2][15] = { "opgeruimde", "smerige" };
	char objects[3][35] = { "met een tafel en vier stoelen", "met in de hoek een bed", "die leeg is" };

	strncpy_s(size, sizes[distribution(generator) - 1], 15);
	strncpy_s(cleanliness, cleanlinesses[distribution(generator) % 2], 15);
	strncpy_s(object, objects[distribution(generator) - 1], 35);

	char description[100] = { "" };

	strcat_s(description, "Het is een ");
	strcat_s(description, size);
	strcat_s(description, " ");
	strcat_s(description, cleanliness);
	strcat_s(description, " ruimte, ");
	strcat_s(description, object);
	strcat_s(description, ".");

	strncpy_s(description_, description, 100);
}

void Room::setRandomItem(std::default_random_engine& generator)
{
	// Generate a possible item, 1/3 chance
	const std::uniform_int_distribution<int> itemChance(1, 3);

	if (itemChance(generator) == 1)
	{
		item_ = nullptr;
		return;
	}

	const std::uniform_int_distribution<int> distribution(1, 3);

	// Choose between 3 item types
	switch (distribution(generator))
	{
	case 1: item_ = new Armor; break;
	case 2: item_ = new Sword; break;
	case 3: // Choose between 3 consumables
		switch (distribution(generator)) {
		case 1: item_ = new HealthPotion; break;
		case 2: item_ = new ExperiencePotion; break;
		case 3: item_ = new HolyGrenade; break;
		}
	}
}
