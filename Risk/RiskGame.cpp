#include "UserInterface.h"
#include "Game.h"
#include <stdlib.h>
#include <iostream>


int main() {
	const auto mapName = UserInterface::selectMap();
	const auto nPlayers = UserInterface::selectNumPlayers();

	Game game = Game(mapName, nPlayers);

	//tests part 2. Edits to Country,Player and Game.
	vector<Player> player = game.getTurns();

    cout<< endl << "Player turn order: ";
    for (int i = 0; i < player.size(); i++) {
        cout << " " << player[i].getID();
    }

    cout << endl;
	for (int i = 0; i < player.size(); i++) {
		cout<< " ~ " << player[i].getID() << " has " << player[i].amtCountries() << " countries and " << player[i].getPlayerArmies() << " armies." <<endl;
        cout << "Countries: ";
        player[i].printCountries();
        cout << endl;;
	}

//	while(player.size() > 1){
//
//        // iterate player turns
//        for (int i = 0; i < player.size(); i++) {
//
//
//        }
//
//	}

    game.fortificationPhase(player[0]);
    
	return 0;
}
