#pragma once
#include "Strategy.h"

class RandomPlayer : public Strategy {
public:
	RandomPlayer() = default;
	void reinforcement(Player* player);
	void attack(Player* player);
	void fortify(Player* player);
};