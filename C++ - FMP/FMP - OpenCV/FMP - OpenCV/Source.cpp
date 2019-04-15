#include "Game.h"

int main()
{
	Game* game = new Game();
	game->Run();
	game->Release();
	delete game;
	game = nullptr;

	return 0;
}