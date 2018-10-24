#include "Room.h"
#include <random>
#include <ctime>
#include "Item/Item.h"
#include "Enemy.h"
#include "Item/Armor.h"
#include "Item/Sword.h"
#include "Item/HealthPotion.h"
#include "Item/ExperiencePotion.h"
#include "Item/HolyGrenade.h"


Room::Room()
{
}

Room::Room(std::default_random_engine& generator, const int floorLevel) : isVisited_{ false }
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

	// Generate a possible item, 1/3 chance
	item_ = getRandomItem(generator);

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

Item* Room::getRandomItem(std::default_random_engine& generator)
{
	const std::uniform_int_distribution<int> itemChance(1, 3);

	if (itemChance(generator) == 1)
		return nullptr;

	const std::uniform_int_distribution<int> distribution(1, 3);

	// Choose between 3 item types
	switch (distribution(generator))
	{
	case 1: return new Armor;
	case 2: return new Sword;
	case 3: // Choose between 3 consumables
		switch (distribution(generator)) {
		case 1: return new HealthPotion;
		case 2: return new ExperiencePotion;
		case 3: return new HolyGrenade;
		}
	}

	return nullptr;
}
