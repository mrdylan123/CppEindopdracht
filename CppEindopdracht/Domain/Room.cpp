#include "Room.h"
#include <random>
#include <ctime>
#include "Enemy.h"
#include <iostream>
#include "../RandomGenerator.h"
#include "../EnemyFactory.h"
#include "Item/Armor.h"
#include "Item/Sword.h"
#include "Item/HealthPotion.h"
#include "Item/ExperiencePotion.h"
#include "Item/DefencePotion.h"


Room::Room(const int floorLevel, const bool containsStairCaseUp, const bool containsStairCaseDown) :
	isVisited_{ false },
	containsStairCaseUp_{ containsStairCaseUp },
	containsStairCaseDown_{ containsStairCaseDown },
	floorLevel_{ floorLevel }
{
	setRandomDescription();
	setRandomItem();

	// TODO: Generate a possible enemy, 1/3 chance
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

Enemy* Room::enemy() const
{
	return enemy_;
}

bool Room::isEnd() const
{
	return isEnd_;
}

char* Room::enemyName() const
{
	return enemy_->name();
}

int Room::floorLevel() const
{
	return floorLevel_;
}

Item* Room::item() const
{
	return item_;
}

Item* Room::pickUpItem()
{
	Item* temp = item_;
	item_ = nullptr;
	return temp;
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
	EnemyFactory* enemyFactory = EnemyFactory::instance();

	enemy_ = enemyFactory->getRandomBoss();

	isEnd_ = true;
}

void Room::setStart()
{
	setVisited();
	isStart_ = true;
}

void Room::setVisited()
{
	isVisited_ = true;
}

void Room::enter(const int dungeonDepth)
{
	isVisited_ = true;

	describe();

	RandomGenerator* generator = RandomGenerator::instance();

	const int enemyChance = generator->randomNumber(1, 3);

	if (!isEnd_ && enemyChance == 1)
	{
		EnemyFactory* enemyFactory = EnemyFactory::instance();

		enemy_ = enemyFactory->getRandomEnemy(floorLevel_, dungeonDepth);
	}

	if (enemy_ != nullptr)
		std::cout << "Aanwezig: In de kamer bevindt zich een " << enemy_->name() << "." << std::endl;

	std::cout << "Wat doe je?" << std::endl;

	std::cout << "Acties: [";

	if (item_ != nullptr)
	{
		std::cout << " zoek |";
	}

	if (enemy_ != nullptr)
	{
		std::cout << " vecht | vlucht |";
	}

	std::cout << " rust | spullen | gebruik | kaart | neemtrap | held ]" << std::endl;
}

void Room::clear()
{
	if (enemy_ != nullptr && !isEnd_)
	{
		delete enemy_;
		enemy_ = nullptr;
	}
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

void Room::setRandomDescription()
{
	RandomGenerator* generator = RandomGenerator::instance();

	// Generate description
	char size[15];
	char cleanliness[15];
	char object[35];

	char sizes[3][15] = { "kleine", "gemiddelde", "grote" };
	char cleanlinesses[2][15] = { "opgeruimde", "smerige" };
	char objects[3][35] = { "met een tafel en vier stoelen", "met in de hoek een bed", "die leeg is" };

	strncpy_s(size, sizes[generator->randomNumber(0, 2)], 15);
	strncpy_s(cleanliness, cleanlinesses[generator->randomNumber(0, 1)], 15);
	strncpy_s(object, objects[generator->randomNumber(0, 2)], 35);

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

void Room::setRandomItem()
{
	// Generate a possible item, 1/3 chance
	RandomGenerator* generator = RandomGenerator::instance();

	if (generator->randomNumber(1, 3) == 1)
	{
		item_ = nullptr;
		return;
	}

	// Choose between 3 item types
	switch (generator->randomNumber(1, 3))
	{
	case 1: item_ = new Armor{ floorLevel_ }; break;
	case 2: item_ = new Sword{ floorLevel_ }; break;
	case 3: // Choose between 3 consumables
		switch (generator->randomNumber(1, 3)) {
		case 1: item_ = new HealthPotion; break;
		case 2: item_ = new ExperiencePotion; break;
		case 3: item_ = new DefencePotion; break;
		}
	}
}

void Room::describe() const
{
	std::cout << description_ << std::endl << std::endl;

	// Staircase
	if (containsStairCaseDown_ || containsStairCaseUp_)
	{
		std::cout << "Er is een trap naar ";

		if (containsStairCaseDown_)
		{
			std::cout << "beneden.";
		}
		else
		{
			std::cout << "boven.";
		}

		std::cout << std::endl << std::endl;
	}

	// Item
	if (item_ != nullptr)
	{
		std::cout << "Er ligt een " << item_->name() << " op de grond." << std::endl << std::endl;
	}

	// Exits
	std::cout << "Uitgangen: ";

	if (northRoom_ != nullptr)
		std::cout << "noord ";

	if (eastRoom_ != nullptr)
		std::cout << "oost ";

	if (southRoom_ != nullptr)
		std::cout << "zuid ";

	if (westRoom_ != nullptr)
		std::cout << "west ";

	std::cout << std::endl << std::endl;
}
