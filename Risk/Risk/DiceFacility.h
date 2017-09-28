#pragma once
#include "Dice.h"
#include <vector>

using std::vector;

class DiceFacility {
	private:
		vector<Dice> _dice;

	public:
		DiceFacility(int numOfDice);
		vector<int> rollDice();
};