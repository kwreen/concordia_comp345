#include "AggressivePlayer.h"
#include "Game.h"
#include "UserInterface.h"
#include <iostream>
#include <string>

void AggressivePlayer::reinforcement(Player* playerptr) {
	Player& player = *playerptr;
	int armiesToAdd = Game::getArmiesToAdd(player);

	int maxArmies = 0;
	std::string strongestCountry;
	
	for (auto& country : player.getCountries()) {
		if (country.getArmies() > maxArmies) {
			maxArmies = country.getArmies();
			strongestCountry = country.getName();
		}
	}

	for (auto& c : player.getCountries()) {
		if (strongestCountry == c.getName()) {
			c.increaseArmiesBy(armiesToAdd);
			std::cout << c.getName() << " now has " << c.getArmies() << " armies after reinforcing. " << std::endl;
		}
	}
}

void AggressivePlayer::attack(Player* playerptr) {
	Player& attacker = *playerptr;
	std::vector<Country> attackingCountries = Game::checkAvailableAttackingCountriesToAttack(attacker);
	bool lostStrongestCountry = false;

	if (attackingCountries.size() > 0) {
		int maxArmies = 0;
		std::string strongestCountry;

		for (auto& country : attacker.getCountries()) {
			if (country.getArmies() > maxArmies) {
				maxArmies = country.getArmies();
				strongestCountry = country.getName();
			}
		}

		for (auto& attackingCountry : attacker.getCountries()) {
			if (strongestCountry == attackingCountry.getName()) {
				std::vector <Country> defendingCountries = Game::checkAvailableDefendingCountriesToAttack(attacker, attackingCountry);

				while (defendingCountries.size() != 0) {
					Country defendingCountry = defendingCountries[0];
					Player& defender = Game::getOwner(defendingCountry);

					int nDiceAttacker = std::max(attackingCountry.getArmies() - 1, 3);
					if (nDiceAttacker > 3) {
						nDiceAttacker = 3;
					}

					int nDiceDefender;
					for (auto& c : defender.getCountries()) {
						if (c.getName() == defendingCountry.getName()) {
							nDiceDefender = std::max(defendingCountry.getArmies(), 2);
							if (nDiceDefender > 2) {
								nDiceDefender = 2;
							}
							break;
						}
					}

					std::cout << "Rolling dice..." << std::endl;
					std::vector<int> attDiceResults = attacker.getDice().rollDice(nDiceAttacker);
					std::vector<int> defDiceResults = defender.getDice().rollDice(nDiceDefender);

					std::cout << "Comparing dice..." << std::endl;
					std::cout << "Attacker rolled...";
					for (const auto& i : attDiceResults) {
						std::cout << " " << i;
					}
					std::cout << std::endl;
					std::cout << "Defender rolled...";
					for (const auto& i : defDiceResults) {
						std::cout << " " << i;
					}
					std::cout << std::endl;

					// Getting the minimum number of dice roll
					int min = std::min(attDiceResults.size(), defDiceResults.size());

					for (int i = 0; i < min; i++) {
						if (attDiceResults[i] > defDiceResults[i]) {
							// Attacker wins
							std::cout << "The attacker has rolled " << attDiceResults[i] << " and the defender has rolled " << defDiceResults[i] << "." << std::endl;
							std::cout << "The defender loses 1 army on " << defendingCountry.getName() << "." << std::endl;

							for (auto& c : defender.getCountries()) {
								if (c.getName() == defendingCountry.getName()) {
									c.decreaseArmiesBy(1);
									if (c.getArmies() == 0) {
										// Moving ONE army from attacking country to defending country
										// Giving defeated country to attacker
										c.increaseArmiesBy(1);
										attacker.getCountries().push_back(Country(c));

										std::cout << c.getName() << " has been defeated. Aggressive Player has moved 1 army to the newly conquered country." << std::endl;

										// Removing defeated country from defender
										const auto pos = std::find(defender.getCountries().begin(), defender.getCountries().end(), c);
										defender.getCountries().erase(pos);
										defendingCountries = Game::checkAvailableDefendingCountriesToAttack(attacker, attackingCountry);
									}
									break;
								}
							}
						}
						else {
							// Defenders wins
							std::cout << "The defender has rolled " << defDiceResults[i] << " and the attacker has rolled " << attDiceResults[i] << "." << std::endl;
							std::cout << "The attacker loses 1 army on " << attackingCountry.getName() << "." << std::endl;

							attackingCountry.decreaseArmiesBy(1);
							if (attackingCountry.getArmies() == 0) {
								// Moving ONE army from defending country to attacking country
								// Giving defeated country to defender
								Country conquered(attackingCountry);
								conquered.increaseArmiesBy(1);
								defender.getCountries().push_back(conquered);

								std::cout << attackingCountry.getName() << " has been defeated. Defender has moved 1 army to the newly conquered country." << std::endl;

								// Removing defeated country from attacker
								const auto pos = std::find(attacker.getCountries().begin(), attacker.getCountries().end(), attackingCountry);
								attacker.getCountries().erase(pos);
								lostStrongestCountry = true;
							}
						}
					}

					if (attackingCountry.getArmies() < 2) {
						std::cout << "Aggressive Player does not have enough armies left on " << strongestCountry << " to attack." << std::endl;
						break;
					}
					else if (lostStrongestCountry) {
						std::cout << "Aggressive player has lost its strongest country, " << strongestCountry << "." << std::endl;
						break;
					}
				}
				break;
			}
		}

	}
	else {
		std::cout << "No available country found for Aggressive Player to attack." << std::endl;
	}
}

void AggressivePlayer::fortify(Player* playerptr) {
	Player& player = *playerptr;
	std::vector<Country> countries = Game::checkAvailableSourceCountriesToFortify(player);

	int maxTargetArmies = 0;
	int maxSourceArmies = 0;
	std::string strongestSource;
	std::string strongestTarget;

	if (countries.size() > 0) {
		for (auto& actual : player.getCountries()) {
			for (auto c : countries) {
				if (actual.getName() == c.getName()) {
					if (actual.getArmies() > maxTargetArmies) {
						maxTargetArmies = actual.getArmies();
						strongestTarget = actual.getName();
					}
					break;
				}
			}
		}

		std::vector<Country> adjacentCountries = Game::checkAvailableTargetCountriesToFortify(player, strongestTarget);
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
			std::cout << "No available country found to fortify Aggressive Player's strongest country, " << strongestTarget << "." << std::endl;
		}
		else {
			for (auto& country : player.getCountries()) {
				if (country.getName() == strongestSource) {
					std::cout << "Aggressive Player has fortified " << strongestTarget << " with " << maxSourceArmies << " armies from " << strongestSource << "." << std::endl;
					country.decreaseArmiesBy(maxSourceArmies);
					std::cout << country.getName() << " now has " << country.getArmies() << " armies." << std::endl;
				}
			}

			for (auto& country : player.getCountries()) {
				if (country.getName() == strongestTarget) {
					country.increaseArmiesBy(maxSourceArmies);
					std::cout << country.getName() << " now has " << country.getArmies() << " armies." << std::endl;
					break;
				}
			}
		}
	}
	else {
		std::cout << "No available country found for Aggressive Player to fortify." << std::endl;
	}
};
