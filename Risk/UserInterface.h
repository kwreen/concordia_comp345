#pragma once

#include <string>
#include "Player.h"
#include "Map.h"

class UserInterface {
public:
	static std::string selectMap();
	static int selectNumPlayers();

	static Country selectCountry(std::vector<Country> countries);
	static Country selectAdjacentCountry(const Country& country, const Map& map, const Player& player);
	static int selectArmiesToFortify(const Country& country);
	static bool toAttackOrNot();
};
