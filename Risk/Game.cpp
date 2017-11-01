#include "Game.h"
#include "MapLoader.h"
#include "UserInterface.h"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <stdlib.h>
#include <time.h>

int Game::getArmiesToAdd(const Player& player) const {
	// Number of countries owned on the map, divided by 3 (rounded down), with a minimum of 3
	int armiesFromCountries = std::min((int) player.getCountries().size() / 3, 3);

	// Continent-control value of all continents totally controlled by that player
	const auto continentsOwned = map.continentsOwned(player);
	int armiesFromContinents = std::accumulate(continentsOwned.begin(), continentsOwned.end(), 0, [&](int i, const std::string& c) {
		return i + map.getContinentValue(c);
	});

	return armiesFromCountries + armiesFromContinents;
}

Player Game::getOwner(const Country& country) const {
	for (const auto& player : turns) {
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
		players.push_back(Player(std::vector<Country>(), Hand(), DiceFacility(),i+1));
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

void Game::startUp() {
	int index = 0;
	for (int i = 0; i < map.getCountries().size(); i++) {
		if (index == numPlayers)
			index = 0; //if index gets after last player,wrap around turns array to start again at player1
		turns[index++].assignCountry(map.getCountries()[i]);

	}
	assignArmies();
}

vector<Player> Game::getTurns() {
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
	startUp();
}

void Game::reinforcementPhase(Player& player) {
	std::cout << "Starting reinforcement phase...\n";

	// Get number of armies to use for reinforcement.
	int armiesFromCardExchange = UserInterface::exchangeCards(player);
	int armiesToAdd = armiesFromCardExchange + getArmiesToAdd(player);

	while (armiesToAdd > 0) {
		// Select country to reinforce
		std::cout << "\nYou have " << armiesToAdd << " remaining soldiers to add. ";
		std::cout << "Please select the country you would like to add soldiers to.\n";
		Country country = UserInterface::selectCountry(player.getCountries());

		// Select number of armies to reinforce for the selected country
		int armies = UserInterface::selectArmiesToReinforce(country, armiesToAdd);
		country.increaseArmiesBy(armies);
		std::cout << country.getName() << " now has " << country.getArmies() << " armies." << std::endl;
		armiesToAdd -= armies;
	}

	std::cout << "\nEnding reinforcement phase.\n";
}

void Game::fortificationPhase(Player& player) {
    std::cout << "Starting fortification phase..." << std::endl;

	std::vector<Country> countries = checkAvailableCountriesToFortify(player);

	if (countries.size() > 0) {
		// Select source and target country to move armies to
		Country source = UserInterface::selectCountry(countries);
		Country target = UserInterface::selectAdjacentCountry(map.adjacent(source));
		int nArmies = UserInterface::selectArmiesToMove(source);
		player.fortify(nArmies, source, target);
	}
	else {
		std::cout << "No available country found to fortify." << std::endl;
	}
	std::cout << "Ending fortification phase..." << std::endl;
}

Map Game::getMap() const {
	return	this->map;
}

std::vector<Country> Game::checkAvailableCountriesToFortify(Player& player) {
	vector<Country> countries = player.getCountries();

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

		if (adjacentCountries.size() == 0) {
			return true;
		}
		else {
			return false;
		}
	}), countries.end());

	return countries;
}

std::vector<Country> Game::checkAvailableCountriesToAttack(Player& player) {
	vector<Country> countries = player.getCountries();

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

		// Removing countries that have no adjacent enemy countries or that have less than 2 armies
		if (adjacentCountries.size() == 0 || c.getArmies() < 2) {
			return true;
		}
		else {
			return false;
		}
	}), countries.end());

	return countries;
}

void Game::attackPhase(Player& attacker) {
	bool toAttack;
	std::cout << "Starting attack phase..." << std::endl;

	do {
		toAttack = UserInterface::toAttackOrNot();

		if (toAttack) {
			std::vector<Country> countries = checkAvailableCountriesToAttack(attacker);

			if (countries.size() > 0) {
				// Select attacking and defending countries
				Country attackingCountry = UserInterface::selectCountry(countries);
				Country fakeDefendingCountry = UserInterface::selectAdjacentCountry(map.adjacent(attackingCountry)); // tmp fix
				Player defender = getOwner(fakeDefendingCountry);
				Country defendingCountry = *std::find(defender.getCountries().begin(), defender.getCountries().end(), fakeDefendingCountry);

				// Select number of dice to roll
				int nDiceAttacker = UserInterface::selectAttackerDice(attackingCountry);
				int nDiceDefender = UserInterface::selectDefenderDice(defendingCountry);

				std::cout << "Rolling dice..." << std::endl;
				vector<int> attDiceResults = attacker.getDice().rollDice(nDiceAttacker);
				vector<int> defDiceResults = defender.getDice().rollDice(nDiceDefender);

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

				// Getting the minium number of dice roll
				int min = std::min(attDiceResults.size(), defDiceResults.size());

				for (int i = 0; i < min; i++) {
					if (attDiceResults[i] > defDiceResults[i]) {
						// Attacker wins
						std::cout << "The attacker has rolled " << attDiceResults[i] << " and the defender has rolled " << defDiceResults[i] << "." << std::endl;
						std::cout << "The defender loses 1 army on " << defendingCountry.getName() << "." << std::endl;
						defendingCountry.decreaseArmiesBy(1);
						//cout << defendingCountry.getArmies();
						if (defendingCountry.getArmies() == 0) {
							std::cout << defendingCountry.getName() << " has been defeated. Attacker must now move armies to the newly conquered country." << std::endl;
							const auto pos = std::find(defender.getCountries().begin(), defender.getCountries().end(), defendingCountry);
							defender.getCountries().erase(pos);
							attacker.getCountries().push_back(defendingCountry);

							int nArmiesToMove = UserInterface::selectArmiesToMove(attackingCountry);
							defendingCountry.increaseArmiesBy(nArmiesToMove);
						}
					}
					else {
						// Defenders wins
						std::cout << "The defender has rolled " << defDiceResults[i] << " and the attacker has rolled " << attDiceResults[i] << "." << std::endl;
						std::cout << "The attacker loses 1 army on " << attackingCountry.getName() << "." << std::endl;
						attackingCountry.decreaseArmiesBy(1);
						if (attackingCountry.getArmies() == 0) {
							std::cout << attackingCountry.getName() << " has been defeated. Defender must now move armies to the newly conquered country." << std::endl;
							const auto pos = std::find(attacker.getCountries().begin(), attacker.getCountries().end(), attackingCountry);
							attacker.getCountries().erase(pos);
							defender.getCountries().push_back(attackingCountry);

							int nArmiesToMove = UserInterface::selectArmiesToMove(defendingCountry);
							attackingCountry.increaseArmiesBy(nArmiesToMove);
						}
					}
				}
			}
			else {
				std::cout << "No available country found to attack." << std::endl;
			}
		}

	} while (toAttack);

	removeDeadPlayers();

	std::cout << "Ending attack phase..." << std::endl;
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
