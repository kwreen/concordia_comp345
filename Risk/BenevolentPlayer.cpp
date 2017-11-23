#include "BenevolentPlayer.h"
#include "Game.h"
#include <iostream>

void BenevolentPlayer::reinforcement(Player* playerptr) {
	Player& player = *playerptr;
	// TODO: GET ARMIES FROM CARD EXCHANGE
	int armiesToAdd = Game::getArmiesToAdd(player);
	std::cout << "Benevolent Player has " << armiesToAdd << " armies for reinforcement." << std::endl;

	int minArmies = INT_MAX;
	std::string weakestCountry;

	for (auto& country : player.getCountries()) {
		if (country.getArmies() < minArmies) {
			minArmies = country.getArmies();
			weakestCountry = country.getName();
		}
	}

	for (auto& c : player.getCountries()) {
		if (weakestCountry == c.getName()) {
			c.increaseArmiesBy(armiesToAdd);
			std::cout << c.getName() << " now has " << c.getArmies() << " armies after reinforcing. " << std::endl;
		}
	}
}

void BenevolentPlayer::attack(Player* playerptr) {
	std::cout << "The Benevolent Player chooses to not attack. " << playerptr->getID() << " has skipped the attack phase." << std::endl;
}

void BenevolentPlayer::fortify(Player* playerptr) {
	Player& player = *playerptr;
	std::vector<Country> countries = Game::checkAvailableSourceCountriesToFortify(player);

	int minTargetArmies = INT_MAX;
	int maxSourceArmies = 0;
	std::string strongestSource;
	std::string weakestTarget;

	if (countries.size() > 0) {
		for (auto& actual : player.getCountries()) {
			for (auto c : countries) {
				if (actual.getName() == c.getName()) {
					if (actual.getArmies() < minTargetArmies) {
						minTargetArmies = actual.getArmies();
						weakestTarget = actual.getName();
					}
					break;
				}
			}
		}

		std::vector<Country> adjacentCountries = Game::checkAvailableTargetCountriesToFortify(player, weakestTarget);
		for (auto& actual : player.getCountries()) {
			for (auto c : adjacentCountries) {
				if (actual.getName() == c.getName()) {
					if (actual.getArmies() > maxSourceArmies) {
						maxSourceArmies = actual.getArmies();
						strongestSource = actual.getName();
					}
					break;
				}
			}
		}

		// Player cannot move all armies from a country to another
		maxSourceArmies -= 1;

		if (maxSourceArmies < 1) {
			std::cout << "No available country found to fortify Benevolent Player's weakest country, " << weakestTarget << "." << std::endl;
		}
		else {
			for (auto& country : player.getCountries()) {
				if (country.getName() == strongestSource) {
					std::cout << "Benevolent Player has fortified " << weakestTarget << " with " << maxSourceArmies << " armies from " << strongestSource << "." << std::endl;
					country.decreaseArmiesBy(maxSourceArmies);
					std::cout << country.getName() << " now has " << country.getArmies() << " armies." << std::endl;
				}
			}

			for (auto& country : player.getCountries()) {
				if (country.getName() == weakestTarget) {
					country.increaseArmiesBy(maxSourceArmies);
					std::cout << country.getName() << " now has " << country.getArmies() << " armies." << std::endl;
					break;
				}
			}
		}
	}
	else {
		std::cout << "No available country found for Benevolent Player to fortify." << std::endl;
	}
}

