#pragma once

#include <string>
#include "Player.h"
#include "Map.h"

class UserInterface {
public:
	static std::string selectMap();
	static int selectNumPlayers();

	static Country selectCountry(std::vector<Country> countries);
	static int selectArmiesToReinforce(const Country& country, int armiesRemaining);
	static int exchangeCards(Player& player);
	static Country selectAdjacentCountry(std::vector<Country> adjacentCountries); // TODO: Updating armies issue
	static int selectArmiesToMove(const Country& country);
	static bool toAttackOrNot();
	static int selectAttackerDice(const Country& attackingCountry);
	static int selectDefenderDice(const Country& defendingCountry);

	// Tournament interactions
	static std::vector<std::string> selectTournamentMaps();
	static std::vector<Player> selectTournamentComputerPlayers();
	static int selectTournamentGames();
	static int selectTournamentTurns();
};
