#pragma once
#include "Strategy.h"

class CheaterPlayer : public Strategy {
public:
	CheaterPlayer() = default;
	void reinforcement(Player* player);
	void attack(Player* player);
	void fortify(Player* player);
};