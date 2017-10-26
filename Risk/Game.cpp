#include "Game.h"
#include "MapLoader.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

void Game::setGameMap(const std::string& mapName) {
	Map map = MapLoader::loadMap(mapName);
	this->map = map;
}

void Game::createPlayers(int nPlayers) {
	for (int i = 0; i < nPlayers; i++) {
		players.push_back(Player(std::vector<Country>(), Hand(), DiceFacility(),i+1));
	}
}

void Game::assignTurns() {
	int numplayers = players.size();
	for(int i = 0; i < numplayers; i++) {
		int r = rand() % players.size();
		turns.push_back(players.at(r));
		players.erase(players.begin() + r);
	}
}

void Game::assignArmies() //again make sure assignTurns is called first
{
	int number; //decides initial number of armies to put on players countries

	if (turns.size() == 2) {
		number = 40;
	}
	else if (turns.size() == 3) {
		number = 35;
	}
	else if (turns.size() == 4) {
		number = 30;
	}
	else if (turns.size() == 5) {
		number = 25;
	}
	else if (turns.size() == 6) {
		number = 20;
	}

	for (int i = 0; i<turns.size(); i++) {
		turns[i].setArmies(number);
		turns[i].initializeArmies();
	}

}

void Game::startUp() //does bulk of part 2. Also again assigntTurns() must be called before this
{
	int index = 0;
	for (int i = 0; i < map.getCountries().size(); i++) //size does =  10
	{
		if (index == numPlayers)
			index = 0; //if index gets after last player,wrap around turns array to start again at player1
		turns[index++].assignCountry(map.getCountries()[i]);

	}
	assignArmies(); //assign armies to these countries

}

vector<Player> Game::getTurns() //returns vector pointer of player turns
{
	return turns;
}

Game::Game(const std::string& fileName, int nPlayers) {
	int random = rand() % 100; //place seed for generator
	srand(random);
	numPlayers = nPlayers;
	setGameMap(fileName);
	deck.loadDeck(map.getCountries());
	createPlayers(nPlayers);
	assignTurns();
	startUp();
}