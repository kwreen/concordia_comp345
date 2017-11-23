#pragma once
#include "Game.h"

class Tournament {

private:
	std::vector<std::vector<Game>> gamesForEachMap;

public:
	void initialize();
	void displayResult();
};