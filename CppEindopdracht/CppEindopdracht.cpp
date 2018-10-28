#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#include "Domain/Dungeon.h"
#include <iostream>
#include "EnemyFactory.h"

int main()
{
	{
		Dungeon dungeon{ 3, 3, 5 };
		//dungeon.showMap();
		dungeon.describeCurrentRoom();

		EnemyFactory* enemyFactory = EnemyFactory::instance();

		char command[30];

		while (true)
		{
			std::cin >> command;

			try
			{
				if (strcmp(command, "noord") == 0)
				{
					dungeon.move(Dungeon::North);
				}
				else if (strcmp(command, "zuid") == 0)
				{
					dungeon.move(Dungeon::South);
				}
				else if (strcmp(command, "oost") == 0)
				{
					dungeon.move(Dungeon::East);
				}
				else if (strcmp(command, "west") == 0)
				{
					dungeon.move(Dungeon::West);
				}
				else if (strcmp(command, "kaart") == 0)
				{
					dungeon.showMap();
				}
			}
			catch (const std::exception& exception)
			{
				std::cout << exception.what() << std::endl;
			}
		}
	}

	_CrtDumpMemoryLeaks();
	return 0;
}

