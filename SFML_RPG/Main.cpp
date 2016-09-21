#include "SFML\Graphics.hpp"

#include "Game.h"
#include "GameMenuState.h"

int main()
{
	// Create Game class
	Game game;

	// Create Game Menu state
	game.pushState(new GameMenuState(&game));

	// Run Game
	game.Run();

	// Clean up Game
	game.cleanUp();

	//system("PAUSE");
	return 0;
}