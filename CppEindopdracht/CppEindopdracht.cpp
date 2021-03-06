#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#include "EnemyFactory.h"
#include "RandomGenerator.h"
#include "Game.h"

int main()
{
	{
		Game game{};
		game.start();

		// Free singleton instance memory
		delete EnemyFactory::instance();
		delete RandomGenerator::instance();
	}

	_CrtDumpMemoryLeaks();
	return 0;
}

