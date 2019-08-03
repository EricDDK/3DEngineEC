#include "iostream"
#include "Common/3DEngine.h"
#include "Game.h"

int main(int argc, char** argv)
{
	engine::Game game;
	bool success = game.init();
	if (success)
	{
		game.runLoop();
	}
	game.shutDown();

#ifdef _MSC_VER
	// system("pause"); // test
#else

#endif
	return 1;
}