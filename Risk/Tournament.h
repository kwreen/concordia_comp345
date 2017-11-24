#pragma once

#include <map>
#include "Game.h"
#include "Map.h"

class Tournament {

private:
	std::vector<std::string> maps;
	std::vector<Player> players;
	int G;
	int D;

	// Map (as in the data structure) between map name and a vector of winners, one for each game.
	std::map<std::string, std::vector<std::string>> winners;

	std::string simulateGame(const std::string& map) const;

public:
	Tournament();

	void startTournament();

	void displayWinners();
};
