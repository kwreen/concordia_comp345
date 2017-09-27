#include "Player.h"
#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

int main() {
	vector<Country> countries;
	Hand hand;
	Dice dice;

	cout << "Creating a player..." << endl;
	Player* player = new Player(countries, hand, dice);
	cout << "Player " << player << " has been created." << endl;
	
	cout << endl;

	cout << "Player " << player << " will now reinforce..."<< endl;
	player->reinforce();
	cout << endl;
	cout << "Player " << player << " will now attack..." << endl;
	player->attack();
	cout << endl;
	cout << "Player " << player << " will now fortify..." << endl;
	player->fortify();

	return 0;
}