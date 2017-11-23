#include <iostream>
#include "Tournament.h"
#include "UserInterface.h"

void Tournament::initialize() {

	int numOfMaps;
	int numOfPlayers;
	int numOfGames;
	int numOfTurns;

	std::vector<std::string> maps;

	for (int i = 0; i<numOfMaps; i++) {
		std::string mapName = UserInterface::selectMap();
		maps.push_back(mapName);
	}

	std::cout << "How many players? (2-4)" << std::endl;
	std::cin >> numOfPlayers;

	std::cout << "How many games? (1-5)" << std::endl;
	std::cin >> numOfGames;

	std::cout << "Maximum number of turns for each game? (10-50)" << std::endl;
	std::cin >> numOfTurns;

	for (int i = 0; i<maps.size(); i++) {
		for (int j = 0; j<numOfGames; j++) {
			// create game
			// Game game = Game(maps[i], numOfPlayers, numOfTurns);
			// gamesForEachMap[i].push_back(game)
		}
	}

}