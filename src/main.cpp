#include "game.h"

int main(int argc, char** argv)
{
	game gameInstance;
	bool success = gameInstance.initialize();
	if (success)
	{
		gameInstance.runLoop();
	}
	gameInstance.shutdown();
	return 0;
}