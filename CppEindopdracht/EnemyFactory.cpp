#include "EnemyFactory.h"
#include <fstream>
#include <iostream>
#include <string>
#include "Domain/Enemy.h"

EnemyFactory *EnemyFactory::s_instance = nullptr;

EnemyFactory::EnemyFactory(): enemies_(new Enemy[14])
{
	std::ifstream inFile;
	inFile.open("Monsters.txt");

	// Check if file can be opened
	if (!inFile)
	{
		std::cerr << "Unable to open file Monsters.txt";
		exit(1); // call system to stop
	}

	// Read every line and copy the values to the enemy array
	while (inFile.good())
	{
		char line[300];
		for (int lineIndex = 0; lineIndex < 14; lineIndex++)
		{
			inFile.getline(line, 300);

			sscanf_s(line, "[%[^;];%d;%dx%d;%d-%d;%d;%d]", enemies_[lineIndex].name_, sizeof enemies_[lineIndex].name_, &enemies_[lineIndex].level_,
				&enemies_[lineIndex].attack_, &enemies_[lineIndex].numberOfAttacks_, &enemies_[lineIndex].minDamage_,
				&enemies_[lineIndex].maxDamage_, &enemies_[lineIndex].defence_, &enemies_[lineIndex].healthPoints_);
		}
	}

	// Close the file once every monster has been read
	inFile.close();
}


EnemyFactory::~EnemyFactory()
{
	delete[] enemies_;
}

// Singleton implementation
EnemyFactory* EnemyFactory::instance()
{
	if (!s_instance)
		s_instance = new EnemyFactory;
	return s_instance;
}

// Enemy* EnemyFactory::GetRandomEnemy(int floorLevel)
// {
//
// }


