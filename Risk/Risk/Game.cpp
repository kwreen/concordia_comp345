#include "Game.h"
#include "../MapLoader.h"
#include "../Player.h"
#include "../Country.h"
#include <iostream>
#include <stdlib.h>
int seed;
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
	for (int i = 0; i < nPlayers; i++) {
		players.push_back(Player(std::vector<Country>(), Hand(), DiceFacility(),i+1));
	}
}
void Game::assignTurns(vector<Player> p) // can only be 2-6 player. Accepts an array of players and gives them randomturns
{
	int numPlayers = p.size();
	
	for (int i = 0; i<numPlayers; i++)
	{
		int r = rand() % numPlayers;
		turns.push_back(p.at(r));
		p.erase(p.begin() + r); //erase player from player array
		numPlayers = p.size();


	}

}
void Game::assignTurns(vector<Player> p) // can only be 2-6 player. Accepts an array of players and gives them randomturns
{
	int numPlayers = p.size();
	int loop = numPlayers;
	for (int i = 0; i<loop; i++)
	{
		int r = rand() % numPlayers;
		turns.push_back(p.at(r));
		p.erase(p.begin() + r); //erase player from player array
		numPlayers = p.size();


	}

}
void Game::assignArmies() //again make sure assignTurns is called first
{
	int number; //decides initial number of armies to put on players countries

	if (turns.size() == 2)
	{
		number = 40;
	}
	else if (turns.size() == 3)
	{
		number = 35;
	}
	else if (turns.size() == 4)
	{
		number = 30;
	}
	else if (turns.size() == 5)
	{
		number = 25;
	}
	else if (turns.size() == 6)
	{
		number = 20;
	}
	else
	{
		cout << "Incorrect number of players";
		return;
	}
	int i = 0;
	while (number>0) //assign total initial armies to players
	{
		if (i>turns.size() - 1) { i = 0; } //wrap around array/round robin logic
		turns[i++].increasePlayerArmies();
		number--;

	}
	for (int i = 0; i<turns.size(); i++) //assign total armies to player countries
	{
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
		turns[index++].assignCountry(map.getCountries[i]); //<--this not insserting at all

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
	assignTurns(players);
	startUp();
}