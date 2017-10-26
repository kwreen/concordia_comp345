#pragma once

#include <string>
#include "Player.h"
#include "Map.h"

class UserInterface {
public:
	static std::string selectMap();
	static int selectNumPlayers();

	static Country selectCountry(const Player& player);
	static Country selectAdjacentCountry(const Country& country, const Map& map);
	static int selectArmiesToFortify(const Country& country);
};
