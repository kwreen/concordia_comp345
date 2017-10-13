#include "DiceRollingFacility.h"

DiceFacility::DiceFacility() {
	for (int i = 0; i < 3; i++) {
		this->_dice[i] = Die();
	}
}

std::array<Die,3> DiceFacility::getDice() const { //returns dice array with all 3 dice
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
	Die die = this->_dice.at(diceNum - 1); //grabs a dice from dice array dice#1 dice#2 or dice#3
	std::array<double, 6> stats = { 0 };

	for (int i = 0; i < stats.size(); i++) {
		stats[i] = die.getPercentageOccurence(i + 1); //stores occurance of 1,2,3,4,5,6 of this particular die
	}

	return stats;
}
