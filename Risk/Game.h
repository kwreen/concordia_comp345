#pragma once

#include "Map.h"
#include "Player.h"
#include "Deck.h"
#include <vector>

class Game {
private:
	Deck deck;
	Map map;
	std::vector<Player> players;

	void setGameMap(const std::string& mapName);
	void createPlayers(int nPlayers);

public:
	Game(const std::string& mapName, int nPlayers);
};