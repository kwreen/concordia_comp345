#include "UserInterface.h"
#include "Game.h"
#include <stdlib.h>
#include <iostream>


int main() {
	const auto mapName = UserInterface::selectMap();
	const auto nPlayers = UserInterface::selectNumPlayers();

	Game game = Game(mapName, nPlayers);

	vector<Player> p = game.getTurns();

	for (int i = 0; i < p.size(); i++) {
		cout<< p[i].getID() << " has " << p[i].amtCountries() << " countries." << endl;
        p[i].printCountries();
	}
	//	cout << "Player a countries: " << endl;

	game.fortificationPhase(p[0]);

	system("pause");
	return 0;
}