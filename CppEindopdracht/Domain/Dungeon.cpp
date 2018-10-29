#include "Dungeon.h"
#include <ctime>
#include <random>
#include <iostream>
#include "Enemy.h"

Dungeon::Dungeon(const int width, const int height, const int depth, Hero* hero) : depth_{ depth }, hero_{ hero }, inCombat_(false),
fleeing_(false), gameOver_(false)
{
	floors_ = new Floor*[depth_];

	for (int i = 0; i < depth; i++)
	{
		floors_[i] = new Floor{ width, height, i, depth_ };
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

	delete hero_;
}

void Dungeon::showMap() const
{
	if (inCombat_)
		throw std::exception{ "Je kan niet op de kaart kijken terwijl je in een gevecht zit." };

	floors_[currentRoom_->floorLevel()]->print();
}

void Dungeon::showItems() const
{
	hero_->printItems();
}

void Dungeon::enter() const
{
	currentRoom_->enter(depth_);
}

void Dungeon::move(const Direction direction)
{
	if (!fleeing_ && currentRoom_->enemy() != nullptr)
		throw std::exception{ "Er is nog een vijand in deze kamer. Typ 'vlucht' om te vluchten." };

	nextRoom(direction);
}

void Dungeon::flee()
{
	fleeing_ = true;
	std::cout << "Welke richting?" << std::endl;

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

void Dungeon::fight()
{
	if (currentRoom_->enemy() == nullptr)
		throw std::exception{ "Er is geen vijand om te bevechten." };

	inCombat_ = true;

	std::cout << "Je bent in gevecht met:" << std::endl;
	currentRoom_->enemy()->describeCondition();
	std::cout << std::endl << "Gebruik [aanval] om aan te vallen" << std::endl;
}

void Dungeon::attack()
{
	if (!inCombat_)
		throw std::exception{ "Je bent niet in een gevecht." };

	if (fleeing_)
		throw std::exception{ "Je bent gevlucht van het gevecht, kies een richting." };

	hero_->attack(*currentRoom_->enemy());

	if (currentRoom_->enemy()->isDead())
	{
		std::cout << "Je hebt de " << currentRoom_->enemy()->name() << " verslagen!" << std::endl;

		if (currentRoom_->isEnd())
		{
			gameOver_ = true;
			std::cout << "Je hebt gewonnen!" << std::endl;
			return;
		}

		hero_->gainExperience(*currentRoom_->enemy());
		currentRoom_->clear();
		currentRoom_->describe();
		std::cout << "Wat doe je?" << std::endl;
		inCombat_ = false;
		fleeing_ = true;
	}
	else
	{
		// Enemy gets to attack the hero
		currentRoom_->enemy()->attack(*hero_);

		if (hero_->isDead())
		{
			gameOver_ = true;
			std::cout << "De " << currentRoom_->enemy()->name() << " heeft je verslagen. Start een nieuw spel om het nog een keer te proberen." << std::endl;
		}
	}
}

void Dungeon::pickUpItem() const
{
	if (currentRoom_->item() == nullptr)
		throw std::exception{ "Er ligt geen item (meer) in deze ruimte." };

	hero_->addItem(currentRoom_->pickUpItem());
}

void Dungeon::useStaircase()
{
	if (currentRoom_->enemy() != nullptr)
		throw std::exception{ "Er is nog een vijand in deze kamer. Kan de trap niet nemen." };

	if (!currentRoom_->containsStairCaseDown() && !currentRoom_->containsStairCaseUp())
		throw std::exception{ "Deze kamer bevat geen trap." };

	int floorLevel = 0;

	// Go up or down the staircase in the current room
	if (currentRoom_->containsStairCaseDown())
	{
		floorLevel = currentRoom_->floorLevel() + 1;
		currentRoom_ = floors_[floorLevel]->stairCaseUpRoom();
	}
	else if (currentRoom_->containsStairCaseUp())
	{
		floorLevel = currentRoom_->floorLevel() - 1;
		currentRoom_ = floors_[floorLevel]->stairCaseDownRoom();
	}

	currentRoom_->enter(depth_);
}

void Dungeon::rest() const
{
	if (currentRoom_->enemy() != nullptr)
		throw std::exception{ "Kan niet uitrusten als er een vijand in de ruimte is." };

	hero_->rest();

	currentRoom_->enter(depth_);
}

bool Dungeon::gameOver() const
{
	return gameOver_;
}

Hero* Dungeon::hero() const
{
	return hero_;
}

void Dungeon::nextRoom(const Direction direction)
{
	Room* nextRoom = nullptr;

	switch (direction)
	{
	case North: nextRoom = currentRoom_->northRoom(); break;
	case East: nextRoom = currentRoom_->eastRoom(); break;
	case South: nextRoom = currentRoom_->southRoom(); break;
	case West: nextRoom = currentRoom_->westRoom(); break;
	}

	// There is no room in that direction
	if (nextRoom == nullptr)
		throw std::exception{ "Kan niet die richting op gaan." };

	currentRoom_->clear();

	fleeing_ = false;
	inCombat_ = false;
	currentRoom_ = nextRoom;

	currentRoom_->enter(depth_);
}
