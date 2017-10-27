#include "Game.h"
#include "MapLoader.h"
#include "UserInterface.h"
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

void Game::assignArmies() {
	int nArmies;

	if (turns.size() == 2) {
		nArmies = 40;
	}
	else if (turns.size() == 3) {
		nArmies = 35;
	}
	else if (turns.size() == 4) {
		nArmies = 30;
	}
	else if (turns.size() == 5) {
		nArmies = 25;
	}
	else if (turns.size() == 6) {
		nArmies = 20;
	}

	for (int i = 0; i<turns.size(); i++) {
		turns[i].setArmies(nArmies);
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

void Game::fortificationPhase(Player& player) {
    std::cout << "Starting fortification phase..." << std::endl;
	
	std::vector<Country> countries = checkAvailableCountriesToFortify(player);

	if (countries.size() > 0) {
		Country country = UserInterface::selectCountry(countries);
		Country adjacentCountry = UserInterface::selectAdjacentCountry(country, map, player);
		int nArmies = UserInterface::selectArmiesToFortify(country);
		player.fortify(nArmies, country, adjacentCountry);
	}
	else {
		std::cout << "No country found." << std::endl;
	}
	std::cout << "Ending fortification phase..." << std::endl;
}

Map Game::getMap() const {
	return	this->map;
}

std::vector<Country> Game::checkAvailableCountriesToFortify(Player& player) {
	vector<Country> countries = player.getCountries();

	// Removing countries from the vector which do not have adjacent countries that the player owns
	countries.erase(std::remove_if(countries.begin(), countries.end(), [&](const Country& c) {
		std::vector<Country> adjacentCountries = map.adjacent(c);
		adjacentCountries.erase(std::remove_if(adjacentCountries.begin(), adjacentCountries.end(), [&](const Country& c) {
			for (auto& country : countries) {
				if (country.getName() == c.getName()) {
					return false;
				}
			}
			return true;
		}), adjacentCountries.end());

		if (adjacentCountries.size() == 0) {
			return true;
		}
		else {
			return false;
		}
	}), countries.end());

	return countries;
}