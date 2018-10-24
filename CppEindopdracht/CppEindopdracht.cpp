#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define DBG_NEW new
#endif

#include "Domain/Dungeon.h"

int main()
{
	{
		Dungeon dungeon{ 3, 3 };
	}
	
	_CrtDumpMemoryLeaks();
    return 0;
}

