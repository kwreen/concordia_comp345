#include "GameStatisticsObserver.h"
#include <iostream>
#include <iomanip>

void GameStatisticsObserver::notifyPhase(int phase) {
	Player& player = *game->getCurrentPlayer();
	// reinforcement
	if (phase == 1) {
		std::cout << "[Phase Observer: " << player.getID() << " stats]" << std::endl;
		std::cout << "Armies: " << player.getPlayerArmies() << ", Cards: " << player.getHand().size() << ", Countries Owned: " << player.getCountries().size() << std::endl;
		std::cout << "\nCountries                          Armies" << std::endl;
		std::cout << "-------------------------------------------" << std::endl;
		for (int i = 0; i < player.getCountries().size(); i++) {
			std::cout << std::left << std::setw(35) << std::setfill(' ') << player.getCountries()[i].getName() << std::left << std::setw(35) << std::setfill(' ') << player.getCountries()[i].getArmies() << std::endl;
		}
		std::cout << std::endl;
	}

	// attack
	else if (phase == 2) {
		std::cout << "[Phase Observer: " << player.getID() << " stats]" << std::endl;
		std::cout << "\nCountries                          Armies" << std::endl;
		std::cout << "-------------------------------------------" << std::endl;
		for (int i = 0; i < player.getCountries().size(); i++) {
			std::cout << std::left << std::setw(35) << std::setfill(' ') << player.getCountries()[i].getName() << std::left << std::setw(35) << std::setfill(' ') << player.getCountries()[i].getArmies() << std::endl;
		}
		std::cout << std::endl;
	}

	// fortification
	else {
		std::cout << "[Phase Observer: " << player.getID() << " stats]" << std::endl;
		std::cout << "\nCountries                          Armies" << std::endl;
		std::cout << "-------------------------------------------" << std::endl;
		for (int i = 0; i < player.getCountries().size(); i++) {
			std::cout << std::left << std::setw(35) << std::setfill(' ') << player.getCountries()[i].getName() << std::left << std::setw(35) << std::setfill(' ') << player.getCountries()[i].getArmies() << std::endl;
		}
		std::cout << std::endl;
	}
}

void GameStatisticsObserver::notifyGame() {
	Player& player = *game->getCurrentPlayer();
	int playerCountries = player.getCountries().size();
	int totalCountries = game->getMap().getCountries().size();
	double percent = (double) playerCountries / totalCountries;

	std::cout << player.getID() << ": " << playerCountries << "/" << totalCountries << ", " << percent * 100 << "% " << "of countries owned." << std::endl;
}