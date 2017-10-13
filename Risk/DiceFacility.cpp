#include "DiceFacility.h"

DiceFacility::DiceFacility() {
	for (int i = 0; i < 3; i++) {
		this->_dice[i] = Die();
	}
}

std::array<Die,3> DiceFacility::getDice() const {
	return this->_dice;
}

std::vector<int> DiceFacility::rollDice(int numOfDice) {
	std::vector<int> dicerollResults;

	for (int i = 0; i < numOfDice; i++) {
		dicerollResults.push_back(this->_dice[i].roll());
	}

	return dicerollResults;
}

std::array<double, 6> DiceFacility::getDiceStats(int diceNum) {
	Die die = this->_dice.at(diceNum - 1);
	std::array<double, 6> stats = { 0 };

	for (int i = 0; i < stats.size(); i++) {
		stats[i] = die.getPercentageOccurence(i + 1);
	}
	
	return stats;
}