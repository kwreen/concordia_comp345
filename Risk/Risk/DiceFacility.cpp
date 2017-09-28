#include "DiceFacility.h"

DiceFacility::DiceFacility(int numOfDice) {
	for (int i = 0; i < numOfDice; i++) {
		this->_dice.push_back(new Dice());
	}
}

DiceFacility::~DiceFacility()
{
	for (int i = 0; i < this->_dice.size(); i++) {
		delete this->_dice.at(i);
	}

	this->_dice.empty();
}

vector<int> DiceFacility::rollDice() {
	vector<int> dicerollResults;

	for (int i = 0; i < this->_dice.size(); i++) {
		dicerollResults.push_back(this->_dice[i]->roll());
	}

	return dicerollResults;
}