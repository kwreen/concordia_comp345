#include "RandomPlayer.h"
#include "Game.h"
#include <algorithm>

// Reinforces a random country
void RandomPlayer::reinforcement(Player* playerptr) {
	Player& player = *playerptr;
	// TODO: GET ARMIES FROM CARD EXCHANGE
	int armiesToAdd = Game::getArmiesToAdd(player);
	int countryIndex = rand() % player.getCountries().size();
	std::cout << "Random Player has " << armiesToAdd << " armies for reinforcement." << std::endl;

	Country& country = player.getCountries()[countryIndex];
	country.increaseArmiesBy(armiesToAdd);
	std::cout << country.getName() << " now has " << country.getArmies() << " armies after reinforcing. " << std::endl;
}

// Attacks a random number of times a random country
void RandomPlayer::attack(Player* playerptr) {
	Player& attacker = *playerptr;
	bool toAttack = rand() % 2;

	do {
		std::vector<Country> attackingCountries = Game::checkAvailableAttackingCountriesToAttack(attacker);

		if (attackingCountries.size() > 0) {
			int attIndex = rand() % attackingCountries.size();
			std::string attCountry = attackingCountries[attIndex].getName();

			for (auto& attackingCountry : attacker.getCountries()) {
				if (attackingCountry.getName() == attCountry) {
					std::vector<Country> defendingCountries = Game::checkAvailableDefendingCountriesToAttack(attacker, attackingCountry);
					int defIndex = rand() % defendingCountries.size();
					std::string defCountry = defendingCountries[defIndex].getName();

					Player& defender = Game::getOwner(defCountry);

					for (auto& defendingCountry : defender.getCountries()) {
						if (defendingCountry.getName() == defCountry) {
							int nDiceAttacker = std::min((rand() % (attackingCountry.getArmies() - 1) + 1), 3);
							int nDiceDefender = std::min((rand() % defendingCountry.getArmies() + 1), 2);

							std::vector<std::vector<int>> diceResults = Game::rollingDice(attacker, defender, nDiceAttacker, nDiceDefender);
							std::vector<int> attDiceResults = diceResults[0];
							std::vector<int> defDiceResults = diceResults[1];

							// Getting the minimum number of dice roll
							int min = std::min(attDiceResults.size(), defDiceResults.size());

							for (int i = 0; i < min; i++) {
								int nArmiesToMove;

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
												nArmiesToMove = (rand() % (attackingCountry.getArmies() - 1) + 1);
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
												nArmiesToMove = (rand() % (defendingCountry.getArmies() - 1) + 1);
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
							toAttack = rand() % 2;
							break;
						}
					}
					break;
				}
			}
		}
		else {
			std::cout << "No available country found for Random Player to attack." << std::endl;
		}
	} while (toAttack);
}

// Fortifies a random country
void RandomPlayer::fortify(Player* playerptr) {
	Player& player = *playerptr;
	int randArmies = 0;
	std::vector<Country> countries = Game::checkAvailableSourceCountriesToFortify(player);
	
	if (countries.size() > 0) {
		int sourceIndex = rand() % countries.size();
		std::string source = countries[rand() % countries.size()].getName();

		std::vector<Country> adjacentCountries = Game::checkAvailableTargetCountriesToFortify(player, countries[sourceIndex]);
		std::string target = adjacentCountries[rand() % adjacentCountries.size()].getName();

		for (auto& c : player.getCountries()) {
			if (c.getName() == source) {
				randArmies = (rand() % (c.getArmies() - 1)) + 1;
				std::cout << "Random Player has fortified " << target << " with " << randArmies << " armies from " << source << "." << std::endl;
				c.decreaseArmiesBy(randArmies);
				std::cout << source << " now has " << c.getArmies() << " armies." << std::endl;
				break;
			}
		}

		for (auto& c : player.getCountries()) {
			if (c.getName() == target) {
				c.increaseArmiesBy(randArmies);
				std::cout << target << " now has " << c.getArmies() << " armies." << std::endl;
				break;
			}
		}
	}
	else {
		std::cout << "No available country found to fortify." << std::endl;
	}
}
