#include "DiceFacility.h"
#include <iostream>

using std::cout;
using std::endl;
using std::cin;

int main() {
	int numOfDice;

	cout << "How many dice would you like to have? (Enter a number from 1 to 3): ";
	cin >> numOfDice;

	cout << endl;
	cout << "Creating " << numOfDice << " dice..." << endl;
	DiceFacility dice(numOfDice);
	cout << numOfDice << " dice have been created." << endl;

	int reroll;

	do {
		cout << endl;
		cout << "Rolling dice..." << endl;
		auto results = dice.rollDice();
		cout << "Dice have been rolled." << endl;

		for (int i = 0; i < results.size(); i++) {
			cout << "Dice " << i << ": " << results.at(i) << endl;
		}

		cout << endl << "Would you like to roll again? ";
		cin >> reroll;
	} while (reroll);

	cout << endl;

	return 0;
}