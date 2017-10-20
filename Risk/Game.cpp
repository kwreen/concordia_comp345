#include "Game.h"
#include "MapLoader.h"
#include <iostream>
#include <stdlib.h>

void Game::setGameMap(const std::string& mapName) {
	Map map = MapLoader::loadMap(mapName);
	
	// Exit if map file is invalid.
	if (map.getCountries().size() == 0) {
		std::cerr << "Invalid map file. Exiting.\n";
		exit(1);
	}

	this->map = map;
}

void Game::createPlayers(int nPlayers) {
	for (int i = 0; i < nPlayers; ++i) {
		players.push_back(Player(std::vector<Country>(), Hand(), DiceFacility()));
	}
}

Game::Game(const std::string& fileName, int nPlayers) {
	setGameMap(fileName);
	deck.loadDeck(map.getCountries());
	createPlayers(nPlayers);
}