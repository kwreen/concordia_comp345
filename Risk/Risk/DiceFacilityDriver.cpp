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
	DiceFacility diceFacility(numOfDice);
	cout << numOfDice << " dice have been created." << endl;

	int reroll;

	do {
		cout << endl;
		cout << "Rolling dice..." << endl;
		auto results = diceFacility.rollDice();
		cout << "Dice have been rolled." << endl;

		for (int i = 0; i < results.size(); i++) {
			cout << "Dice " << i << ": " << results.at(i) << endl;
		}

		cout << endl << "Would you like to roll again? (Enter 0 for NO)";
		cin >> reroll;
	} while (reroll);

	cout << endl;
	cout << "Here are the results of your " << numOfDice << " dice rolls:" << endl;

	return 0;
}