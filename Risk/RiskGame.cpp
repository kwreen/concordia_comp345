#include "Risk/UserInterface.h"
#include "Risk/Game.h"
#include <stdlib.h>
#include <iostream>


int main() {
	const auto mapName = UserInterface::selectMap();
	const auto nPlayers = UserInterface::selectNumPlayers();

	Game game(mapName, nPlayers);
	system("pause");
}