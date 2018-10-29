#include "Game.h"
#include <ostream>
#include <iostream>
#include "HeroLoader.h"
#include "Domain/Hero.h"
#include "Domain/Dungeon.h"
#include <iomanip>


Game::Game()
{
	std::cout << "Wil je een bestaande held laden [laad] of een nieuwe [nieuw] maken?" << std::endl;

	char command[30];

	// Create or load a hero
	heroLoader_ = new HeroLoader;
	
	Hero* hero = nullptr;

	while (hero == nullptr)
	{
		std::cin >> std::setw(30) >> command;

		if (strcmp(command, "nieuw") == 0)
		{
			hero = newHero();
		}
		else if (strcmp(command, "laad") == 0)
		{
			std::cout << "Opgeslagen helden: " << std::endl;

			if (heroLoader_->showSavedHeroes())
			{
				std::cout << std::endl << "Welke held wil je inladen?" << std::endl;

				int heroIndex;
				std::cin >> std::setw(2) >> heroIndex;

				hero = heroLoader_->loadHero(heroIndex);
			}
			else
			{
				std::cout << "Er zijn geen opgeslagen helden." << std::endl;

				hero = newHero();
			}
		}
	}

	std::cout << "Geef een x" << std::endl;
	int x;
	std::cin >> std::setw(1) >> x;

	if (x == 0)
		x = 1;

	std::cout << "Geef een y" << std::endl;
	int y;
	std::cin >> std::setw(1) >> y;

	if (y == 0)
		y = 1;

	std::cout << "Geef een diepte" << std::endl;
	int depth;
	std::cin >> std::setw(1) >> depth;

	if (depth == 0)
		depth = 1;

	dungeon_ = new Dungeon{ x, y, depth, hero };
	dungeon_->enter();
}


Game::~Game()
{
	delete dungeon_;
	delete heroLoader_;
}

void Game::start() const
{
	char command[30];

	bool running = true;

	while (running)
	{
		std::cin >> std::setw(30) >> command;
		std::cout << std::endl;

		try
		{
			if (!dungeon_->gameOver())
			{
				if (strcmp(command, "noord") == 0)
				{
					dungeon_->move(Dungeon::North);
				}
				else if (strcmp(command, "zuid") == 0)
				{
					dungeon_->move(Dungeon::South);
				}
				else if (strcmp(command, "oost") == 0)
				{
					dungeon_->move(Dungeon::East);
				}
				else if (strcmp(command, "west") == 0)
				{
					dungeon_->move(Dungeon::West);
				}
				else if (strcmp(command, "kaart") == 0)
				{
					dungeon_->showMap();
				}
				else if (strcmp(command, "vecht") == 0)
				{
					dungeon_->fight();
				}
				else if (strcmp(command, "vlucht") == 0)
				{
					dungeon_->flee();
				}
				else if (strcmp(command, "aanval") == 0)
				{
					dungeon_->attack();
				}
				else if (strcmp(command, "zoek") == 0)
				{
					dungeon_->pickUpItem();
				}
				else if (strcmp(command, "spullen") == 0)
				{
					dungeon_->showItems();
				}
				else if (strcmp(command, "gebruik") == 0)
				{
					std::cout << "Welke wil je gebruiken? Geef de positie van het item in je inventaris." << std::endl;
					dungeon_->showItems();

					int item = -1;

					std::cin >> std::setw(1) >> item;

					dungeon_->hero()->useItem(item);
				}
				else if (strcmp(command, "held") == 0)
				{
					dungeon_->hero()->describeCondition();
				}
				else if (strcmp(command, "neemtrap") == 0)
				{
					dungeon_->useStaircase();
				}
				else if (strcmp(command, "rust") == 0)
				{
					dungeon_->rest();
				}
			}
			else
			{
				std::cout << "Kan deze actie niet uitvoeren. Start een nieuwe game om opnieuw te proberen." << std::endl;
			}

			if (strcmp(command, "exit") == 0)
			{
				std::cout << "Wil je je huidige held opslaan? [ja/nee]" << std::endl;

				char save[4];

				std::cin >> std::setw(4) >> save;

				if (strcmp(save, "ja") == 0)
				{
					heroLoader_->saveHero(dungeon_->hero());
				}

				running = false;
			}
		}
		catch (const std::exception& exception)
		{
			std::cout << exception.what() << std::endl;
		}

		std::cout << std::endl;
	}
}

Hero* Game::newHero() const
{
	std::cout << "Geef een naam voor je nieuwe held:" << std::endl;

	char* name = new char[30];
	std::cin >> std::setw(30) >> name;

	return new Hero{ name };
}
