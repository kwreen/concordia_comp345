#pragma once
#include "Die.h"
#include <vector>

class DiceFacility {
	private:
		std::vector<Die> _dice;

	public:
		DiceFacility(int numOfDice);
		std::vector<Die> const &getDice() const;
		std::vector<int> rollDice();
};