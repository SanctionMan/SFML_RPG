#include "SFML\Graphics.hpp"

#include "Game.h"
#include "GameMenuState.h"

int main()
{
	// Create Game classsds
	Game game;

	// Create Game Menu state
	//game.pushState(new GameMenuState(&game));

	//Run Game
	game.Run();

	// Clean up Game
	game.cleanUp();

	return 0;
}


