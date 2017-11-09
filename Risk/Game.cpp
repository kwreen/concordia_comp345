#include "Game.h"
#include "MapLoader.h"
#include "UserInterface.h"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <stdlib.h>
#include <time.h>
#include "HumanPlayer.h"

int Game::getArmiesToAdd(const Player& player) const {
    // Number of countries owned on the map, divided by 3 (rounded down), with a minimum of 3
    int armiesFromCountries = std::max((int) player.getCountries().size() / 3, 3);

    // Continent-control value of all continents totally controlled by that player
    const auto continentsOwned = map.continentsOwned(player);
    int armiesFromContinents = std::accumulate(continentsOwned.begin(), continentsOwned.end(), 0, [&](int i, const std::string& c) {
        return i + map.getContinentValue(c);
    });

    return armiesFromCountries + armiesFromContinents;
}

Player& Game::getOwner(const Country& country) {
    for (auto& player : turns) {
        for (const auto& c : player.getCountries()) {
            if (c == country) {
                return player;
            }
        }
    }
}

void Game::setGameMap(const std::string& mapName) {
    Map map = MapLoader::loadMap(mapName);
    this->map = map;
}

void Game::createPlayers(int nPlayers) {
    for (int i = 0; i < nPlayers; i++) {
        players.push_back(Player(std::vector<Country>(), Hand(), DiceFacility(),i+1, new HumanPlayer()));
    }
}

void Game::assignTurns() {
    int numplayers = players.size();
    for(int i = 0; i < numplayers; i++) {
        int r = rand() % players.size();
        turns.push_back(players.at(r));
        players.erase(players.begin() + r);
    }
}

void Game::assignArmies() {
    int nArmies;

    if (turns.size() == 2) {
        nArmies = 40;
    }
    else if (turns.size() == 3) {
        nArmies = 35;
    }
    else if (turns.size() == 4) {
        nArmies = 30;
    }
    else if (turns.size() == 5) {
        nArmies = 25;
    }
    else if (turns.size() == 6) {
        nArmies = 20;
    }

    for (int i = 0; i<turns.size(); i++) {
        turns[i].setArmies(nArmies);
        turns[i].initializeArmies();
    }
}

void Game::assignObservers() {
    for (auto& player : turns){
        attach(&player);
    }
    setTotalCountries(map.getCountries().size());
}

void Game::startUp() {
    int index = 0;
    for (int i = 0; i < map.getCountries().size(); i++) {
        if (index == numPlayers)
            index = 0; //if index gets after last player,wrap around turns array to start again at player1
        turns[index++].assignCountry(map.getCountries()[i]);

    }
    assignArmies();
}

std::vector<Player>& Game::getTurns() {
    return turns;
}
Game::Game(const std::string& fileName, int nPlayers) {
    int random = rand() % 100; //place seed for generator
    srand(random);
    numPlayers = nPlayers;
    setGameMap(fileName);
    deck.loadDeck(map.getCountries());
    createPlayers(nPlayers);
    assignTurns();
    assignObservers();
    startUp();
}

void Game::reinforcementPhase(Player& player) {
    currentPhase = 1;
    setPhase(currentPhase);

    notifyGameAll();
	notifyPhaseAll();

    player.getStrategy()->reinforcement();

    // Get number of armies to use for reinforcement.
    int armiesFromCardExchange = UserInterface::exchangeCards(player);
    int armiesToAdd = armiesFromCardExchange + getArmiesToAdd(player);
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
			}
		}
        armiesToAdd -= armies;
    }
}

void Game::fortificationPhase(Player& player) {
    currentPhase = 3;
    setPhase(currentPhase);

    notifyGameAll();
	notifyPhaseAll();

    std::vector<Country> countries = checkAvailableSourceCountriesToFortify(player);

	if (countries.size() > 0) {
		// Select source and target country to move armies to
		Country source = UserInterface::selectCountry(countries);
		std::vector<Country> adjacentCountries = checkAvailableTargetCountriesToFortify(player, source);
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

Map Game::getMap() const {
    return	this->map;
}

std::vector<Country> Game::checkAvailableSourceCountriesToFortify(Player& player) {
    std::vector<Country> countries = player.getCountries();

    // Removing countries from the vector which do not have adjacent countries that the player owns
    countries.erase(std::remove_if(countries.begin(), countries.end(), [&](const Country& c) {
        std::vector<Country> adjacentCountries = map.adjacent(c);
        adjacentCountries.erase(std::remove_if(adjacentCountries.begin(), adjacentCountries.end(), [&](const Country& c) {
            for (auto& country : countries) {
                if (country.getName() == c.getName()) {
                    return false;
                }
            }
            return true;
        }), adjacentCountries.end());

		// If the country has no adjacent countries, remove from available source countries
        if (adjacentCountries.size() == 0) {
            return true;
        }
        else {
            return false;
        }
    }), countries.end());

    return countries;
}

std::vector<Country> Game::checkAvailableTargetCountriesToFortify(Player& player, Country source) {
	std::vector<Country> countries = player.getCountries();
	std::vector<Country> adjacentCountries = map.adjacent(source);

	// Removing adjacent countries to the Source that the player does not own
	adjacentCountries.erase(std::remove_if(adjacentCountries.begin(), adjacentCountries.end(), [&](const Country& c) {
		for (auto& country : countries) {
			if (country.getName() == c.getName()) {
				return false;
			}
		}
		return true;
	}), adjacentCountries.end());

	return adjacentCountries;
}

std::vector<Country> Game::checkAvailableAttackingCountriesToAttack(Player& player) {
    std::vector<Country> countries = player.getCountries();

    // Removing countries from the vector which have adjacent countries that the player owns
    countries.erase(std::remove_if(countries.begin(), countries.end(), [&](const Country& c) {
        std::vector<Country> adjacentCountries = map.adjacent(c);
        adjacentCountries.erase(std::remove_if(adjacentCountries.begin(), adjacentCountries.end(), [&](const Country& c) {
            for (auto& country : countries) {
                if (country.getName() == c.getName()) {
                    return true;
                }
            }
            return false;
        }), adjacentCountries.end());

        // Removing countries that have no adjacent enemy countries or that don't have at least 2 armies
        if (adjacentCountries.size() == 0 || c.getArmies() < 2) {
            return true;
        }
        else {
            return false;
        }
    }), countries.end());

    return countries;
}

std::vector<Country> Game::checkAvailableDefendingCountriesToAttack(Player& player, Country source) {
	std::vector<Country> countries = player.getCountries();
	std::vector<Country> adjacentCountries = map.adjacent(source);

	// Removing adjacent countries to the Source that the player does not own
	adjacentCountries.erase(std::remove_if(adjacentCountries.begin(), adjacentCountries.end(), [&](const Country& c) {
		for (auto& country : countries) {
			if (country.getName() == c.getName()) {
				return true;
			}
		}
		return false;
	}), adjacentCountries.end());

	return adjacentCountries;
}

void Game::attackPhase(Player& attacker) {
    currentPhase = 2;
    setPhase(currentPhase);

    notifyGameAll();
	notifyPhaseAll();

    bool toAttack;

    do {
        toAttack = UserInterface::toAttackOrNot();

        if (toAttack) {
            std::vector<Country> attackingCountries = checkAvailableAttackingCountriesToAttack(attacker);

            if (attackingCountries.size() > 0) {
                // Select attacking and defending countries
                Country attackingCountry = UserInterface::selectCountry(attackingCountries);
				std::vector <Country> defendingCountries = checkAvailableDefendingCountriesToAttack(attacker, attackingCountry);
                Country defendingCountry = UserInterface::selectAdjacentCountry(defendingCountries);
                Player& defender = getOwner(defendingCountry);

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
                std::cout << "No available country found to attack." << std::endl;
            }
        }

    } while (toAttack);

	// TODO: detach players from Game
    removeDeadPlayers();

}

void Game::removeDeadPlayers() {
    std::vector<int> playersIndicesToDelete;
    for (int i = 0; i < players.size(); ++i) {
        const auto player = players[i];
        if (player.getCountries().empty()) {
            playersIndicesToDelete.push_back(i);
        }
    }

    for (int i : playersIndicesToDelete) {
        players.erase(players.begin() + i);
    }
}

Deck Game::getDeck() {
    return deck;
}
