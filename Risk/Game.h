#pragma once

#include "Map.h"
#include "Player.h"
#include "Deck.h"
#include "Country.h"
#include <vector>

class Game {

private:
	Deck deck;
	Map map;
	std::vector<Player> players;
	std::vector<Player> turns;
	int numPlayers;

	void setGameMap(const std::string& mapName);
	void createPlayers(int nPlayers);
	void assignTurns();
	void startUp();
	void assignArmies();
	//vector<Player> getTurns();

public:
	Game(const std::string& mapName, int nPlayers);
	vector<Player> getTurns();
	vector<Player> getUnorderedPlayers() { return players;}
};