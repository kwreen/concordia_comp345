#include "Dice.h"
#include <time.h>
#include <random>

bool Dice::_seededRand = false;

Dice::Dice() {
	this->_totalRollCount = 0;
	for (int i = 0; i < 6; i++) {
		this->_occurenceCount[i] = 0;
	}
}

int Dice::roll() {
	// Seed the random number generator if haven't already.
	if (!Dice::_seededRand) {
		srand(time(NULL));
		Dice::_seededRand = true;
	}

	int randomNum = (rand() % 6) + 1;
	this->_totalRollCount++;
	this->_occurenceCount[randomNum - 1]++;

	return randomNum;
}

double Dice::getPercentageOccurence(int value) {
	return (double) this->_occurenceCount[value - 1] / this->_totalRollCount;
}