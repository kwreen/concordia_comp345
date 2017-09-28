#include "Die.h"
#include <time.h>
#include <random>

bool Die::_seededRand = false;

Die::Die() {
	this->_totalRollCount = 0;
	for (int i = 0; i < 6; i++) {
		this->_occurenceCount[i] = 0;
	}
}

int Die::roll() {
	// Seed the random number generator if haven't already.
	if (!Die::_seededRand) {
		srand(time(NULL));
		Die::_seededRand = true;
	}

	int randomNum = (rand() % 6) + 1;
	this->_totalRollCount++;
	this->_occurenceCount[randomNum - 1]++;

	return randomNum;
}

double Die::getPercentageOccurence(int value) {
	return (double) this->_occurenceCount[value - 1] / this->_totalRollCount;
}