#include "HumanPlayer.h"
#include "Country.h"
#include "UserInterface.h"
#include "Game.h"
#include <iostream>
#include <vector>

void HumanPlayer::reinforcement(Player* playerptr) {
	Player& player = *playerptr;
	// Get number of armies to use for reinforcement.
	int armiesFromCardExchange = UserInterface::exchangeCards(player);
	int armiesToAdd = armiesFromCardExchange + Game::getArmiesToAdd(player);
	int x = 0;
	while (armiesToAdd > 0) {
		// Select country to reinforce
		std::cout << "\nYou have " << armiesToAdd << " remaining soldiers to add. ";
		std::cout << "Please select the country you would like to add soldiers to.\n";
		Country country = UserInterface::selectCountry(player.getCountries());

		//// Select number of armies to reinforce for the selected country
		int armies = UserInterface::selectArmiesToReinforce(country, armiesToAdd);
		for (auto& c : player.getCountries()) {
			if (c.getName() == country.getName()) {
				c.increaseArmiesBy(armies);
				std::cout << c.getName() << " now has " << c.getArmies() << " armies after reinforcing. " << std::endl;
			}
		}
		armiesToAdd -= armies;
	}
}

void HumanPlayer::attack(Player* playerptr) {
	Player& attacker = *playerptr;
	bool toAttack;

	do {
		toAttack = UserInterface::toAttackOrNot();

		if (toAttack) {
			std::vector<Country> attackingCountries = Game::checkAvailableAttackingCountriesToAttack(attacker);

			if (attackingCountries.size() > 0) {
				// Select attacking and defending countries
				Country attackingCountry = UserInterface::selectCountry(attackingCountries);
				std::vector <Country> defendingCountries = Game::checkAvailableDefendingCountriesToAttack(attacker, attackingCountry);
				Country defendingCountry = UserInterface::selectAdjacentCountry(defendingCountries);
				Player& defender = Game::getOwner(defendingCountry);

				// Select number of dice to roll
				int nDiceAttacker;
				for (auto& c : attacker.getCountries()) {
					if (c.getName() == attackingCountry.getName()) {
						nDiceAttacker = UserInterface::selectAttackerDice(c);
						break;
					}
				}

				int nDiceDefender;
				for (auto& c : defender.getCountries()) {
					if (c.getName() == defendingCountry.getName()) {
						nDiceDefender = UserInterface::selectDefenderDice(c);
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
									std::cout << c.getName() << " has been defeated. Attacker must now move armies to the newly conquered country." << std::endl;

									// Moving armies from attacking country to defending country
									// Giving defeated country to attacker
									int nArmiesToMove = UserInterface::selectArmiesToMove(attackingCountry);
									c.increaseArmiesBy(nArmiesToMove);
									attacker.getCountries().push_back(Country(c));

									// Removing defeated country from defender
									const auto pos = std::find(defender.getCountries().begin(), defender.getCountries().end(), c);
									defender.getCountries().erase(pos);
								}
								break;
							}
						}
					}
					else {
						// Defenders wins
						std::cout << "The defender has rolled " << defDiceResults[i] << " and the attacker has rolled " << attDiceResults[i] << "." << std::endl;
						std::cout << "The attacker loses 1 army on " << attackingCountry.getName() << "." << std::endl;

						for (auto& c : attacker.getCountries()) {
							if (c.getName() == attackingCountry.getName()) {
								c.decreaseArmiesBy(1);
								if (c.getArmies() == 0) {
									std::cout << attackingCountry.getName() << " has been defeated. Defender must now move armies to the newly conquered country." << std::endl;

									// Moving armies from defending country to attacking country
									// Giving defeated country to defender
									int nArmiesToMove = UserInterface::selectArmiesToMove(defendingCountry);
									c.increaseArmiesBy(nArmiesToMove);
									defender.getCountries().push_back(Country(c));

									// Removing defeated country from attacker
									const auto pos = std::find(attacker.getCountries().begin(), attacker.getCountries().end(), c);
									attacker.getCountries().erase(pos);
								}
								break;
							}
						}
					}
				}
			}
			else {
				std::cout << "No available country found for Human Player attack." << std::endl;
			}
		}

	} while (toAttack);
}

void HumanPlayer::fortify(Player* playerptr) {
	Player& player = *playerptr;
	std::vector<Country> countries = Game::checkAvailableSourceCountriesToFortify(player);

	if (countries.size() > 0) {
		// Select source and target country to move armies to
		Country source = UserInterface::selectCountry(countries);
		std::vector<Country> adjacentCountries = Game::checkAvailableTargetCountriesToFortify(player, source);
		Country target = UserInterface::selectAdjacentCountry(adjacentCountries);
		int nArmies = UserInterface::selectArmiesToMove(source);

		for (auto& c : player.getCountries()) {
			if (c.getName() == source.getName()) {
				c.decreaseArmiesBy(nArmies);
				std::cout << c.getName() << " now has " << c.getArmies() << " armies." << std::endl;
				break;
			}
		}

		for (auto& c : player.getCountries()) {
			if (c.getName() == target.getName()) {
				c.increaseArmiesBy(nArmies);
				std::cout << c.getName() << " now has " << c.getArmies() << " armies." << std::endl;
				break;
			}
		}

		std::cout << nArmies << " have been moved from " << source.getName() << " to " << target.getName() << std::endl;
	}
	else {
		std::cout << "No available country found to fortify." << std::endl;
	}
}
