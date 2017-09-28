#include "DiceFacility.h"

DiceFacility::DiceFacility(int numOfDice) {
	for (int i = 0; i < numOfDice; i++) {
		this->_dice.push_back(Die());
	}
}

std::vector<Die> const &DiceFacility::getDice() const {
	return this->_dice;
}

std::vector<int> DiceFacility::rollDice() {
	std::vector<int> dicerollResults;

	for (int i = 0; i < this->_dice.size(); i++) {
		dicerollResults.push_back(this->_dice[i].roll());
	}

	return dicerollResults;
}