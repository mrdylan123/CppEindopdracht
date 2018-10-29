#include "HeroLoader.h"
#include <cstdlib>
#include <iostream>
#include "Domain/Hero.h"
#include <fstream>
#include <string>


HeroLoader::HeroLoader()
{
}


HeroLoader::~HeroLoader()
{
}

bool HeroLoader::showSavedHeroes() const
{
	std::ifstream inFile;
	inFile.open("Heroes.txt");

	// Check if file can be opened
	if (!inFile)
	{
		std::cerr << "Unable to open file Heroes.txt";
		exit(1); // call system to stop
	}

	int count = 0;

	while (inFile.good())
	{
		char line[300];

		inFile.getline(line, 300);

		if (strcmp(line, "") == 0)
			continue;

		std::cout << "[" << count << "] " << line << std::endl;
		count++;
	}

	// Close the file once the heroes have been read
	inFile.close();

	return count != 0;
}

Hero* HeroLoader::loadHero(const int index) const
{
	std::ifstream inFile;
	inFile.open("Heroes.txt");

	// Check if file can be opened
	if (!inFile)
	{
		std::cerr << "Unable to open file Heroes.txt";
		exit(1); // call system to stop
	}

	Hero* hero = new Hero{};

	int lineCount = 0;

	while (inFile.good() && index >= lineCount)
	{
		char line[300];

		// Skip lines up to the given index
		for (int lineIndex = 0; lineIndex < index; lineIndex++)
			inFile.getline(line, 300);

		inFile.getline(line, 300);

		sscanf_s(line, "[%[^;];%d;%d;%d-%d;%d;%d;%d]", hero->name_, 30, &hero->level_,
			&hero->attackChance_, &hero->minDamage_, &hero->maxDamage_, &hero->defenceChance_, &hero->healthPoints_, &hero->experiencePoints_);

		lineCount++;
	}

	// Close the file once the hero has been read
	inFile.close();

	return hero;
}

void HeroLoader::saveHero(Hero* hero) const
{
	std::ofstream heroFile("Heroes.txt", std::fstream::app);

	char format[] = "[%s;%d;%d;%d-%d;%d;%d;%d]";
	char heroLine[1000];

	// Format the hero into a string
	sprintf_s(heroLine, format, hero->name_, hero->level_,
		hero->attackChance_, hero->minDamage_, hero->maxDamage_, hero->defenceChance_, hero->healthPoints_, hero->experiencePoints_);

	char line[300];

	if (heroFile.is_open())
	{

		heroFile << heroLine << std::endl;
		heroFile.close();
	}
	else std::cerr << "Unable to open file";
}
