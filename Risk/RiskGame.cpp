#include "UserInterface.h"
#include "Game.h"
#include <stdlib.h>
#include <iostream>


int main() {
	const auto mapName = UserInterface::selectMap();
	const auto nPlayers = UserInterface::selectNumPlayers();

	Game game = Game(mapName, nPlayers);

	//tests part 2. Edits to Country,Player and Game.
	vector<Player> players = game.getTurns();

    cout<< endl << "Player turn order: ";
    for (int i = 0; i < players.size(); i++) {
        cout << " " << players[i].getID();
    }

    cout << endl;
	for (int i = 0; i < players.size(); i++) {
		cout<< " ~ " << players[i].getID() << " has " << players[i].amtCountries() << " countries and " << players[i].getPlayerArmies() << " armies." <<endl;
        cout << "Countries: ";
        players[i].printCountries();
        cout << endl;;
	}

	while (game.getTurns().size() > 1) {
		for (auto& player : players) {
			std::cout << "\n\nPlayer " << player.getIDAsInt() << " turn.\n";
			game.reinforcementPhase(player);
			game.attackPhase(player);
			game.fortificationPhase(player);
		}
	}

    cout << " The game is over and player " << players[0].getIDAsInt() << " has won.";


	return 0;
}
