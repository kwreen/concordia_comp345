#pragma once

#include <string>
#include "Player.h"
#include "Map.h"

class UserInterface {
public:
	static std::string selectMap();
	static int selectNumPlayers();

	static Country& selectCountry(Player& player);
	static Country selectAdjacentCountry(Country& country, Map map);
	static int selectArmiesToFortify(Country& country);
};
