#pragma once
#include "Die.h"
#include <vector>
#include <array>

class DiceFacility {
	private:
		std::array<Die, 3> _dice; //put 1 die at each index

	public:
		DiceFacility();
		std::array<Die, 3> getDice() const;
		std::vector<int> rollDice(int numOfDice); //this returns result of rolling a dice at a particular time
		std::array<double, 6> getDiceStats(int diceNum);
};
