#include "SFML\Graphics.hpp"

#include "Game.h"
#include "MenuState.h"

int main()
{

	Game game;

	game.pushState(new MenuState(&game));
	game.Run();
	game.cleanUp();


	//system("PAUSE");
	return 0;
}