#include "Player.h"
#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

int mainbutnotreally() {
	vector<Country> countries;
	Hand hand;
	DiceFacility dice;
	cout << "Creating a player..." << endl;
	Player player (countries, hand, dice);
	cout << "A player has been created." << endl;
	
	cout << endl;

	cout << "The player will now reinforce..."<< endl;
	player.reinforce();
	cout << endl;
	cout << "The player will now attack..." << endl;
	player.attack();
	cout << endl;
	cout << "The player will now fortify..." << endl;
	player.fortify();

	return 0;
}