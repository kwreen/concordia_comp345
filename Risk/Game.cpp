#include "Game.h"
#include "MapLoader.h"
#include "UserInterface.h"
#include "HumanPlayer.h"
#include "AggressivePlayer.h"
#include "BenevolentPlayer.h"
#include "GameStatisticsObserver.h"
#include "ObserverDecorator.h"
#include "PlayerDominationObserverDecorator.h"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <stdlib.h>
#include <time.h>

Map Game::map = Map();
std::vector<Player> Game::turns = {};

int Game::getArmiesToAdd(const Player& player) {
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
		if (i == 1) {
			players.push_back(Player(std::vector<Country>(), Hand(), DiceFacility(), i + 1, new BenevolentPlayer()));
		}
		else if (i == 2) {
			players.push_back(Player(std::vector<Country>(), Hand(), DiceFacility(), i + 1, new AggressivePlayer()));
		}
		else {
			players.push_back(Player(std::vector<Country>(), Hand(), DiceFacility(), i + 1, new HumanPlayer()));
		}
    }
}

void Game::assignTurns() {
    int numplayers = players.size();
    for (int i = 0; i < numplayers; i++) {
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
	attach(new ObserverDecorator(new GameStatisticsObserver(this)));
	attach(new PlayerDominationObserverDecorator(new GameStatisticsObserver(this)));
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
    srand(time(NULL));
    numPlayers = nPlayers;
    setGameMap(fileName);
    deck.loadDeck(map.getCountries());
    createPlayers(nPlayers);
    assignTurns();
	currentPlayer = &turns[0];
    assignObservers();
    startUp();
}

Game::Game(const std::string& mapName, const std::vector<Player>& players) {
	srand(time(NULL));
	numPlayers = players.size();
	setGameMap(mapName);
	deck.loadDeck(map.getCountries());
	this->players = players;
	turns.erase(turns.begin(), turns.end());
	assignTurns();
	currentPlayer = &turns[0];
	assignObservers();
	startUp();
}

void Game::reinforcementPhase(Player& player) {
    currentPhase = 1;
    setPhase(currentPhase);

    player.executeReinforcement(&player);

	notify();
}

void Game::fortificationPhase(Player& player) {
    currentPhase = 3;
    setPhase(currentPhase);

	player.executeFortify(&player);

	// Update current player
	for (int i = 0; i < turns.size(); i++) {
		if (turns[i].getID() == currentPlayer->getID()) {
			currentPlayer = &turns[(i + 1) % turns.size()];
		}
	}

	++turnNumber;

	notify();
}

Map Game::getMap() const {
    return	this->map;
}

std::vector<Country> Game::checkAvailableSourceCountriesToFortify(Player& player) {
    std::vector<Country> countries = player.getCountries();

    // Removing countries from the vector which do not have adjacent countries that the player owns
    countries.erase(std::remove_if(countries.begin(), countries.end(), [&](const Country& c) {
		if (c.getArmies() <= 1) {
			return true;
		}

        std::vector<Country> adjacentCountries = Game::map.adjacent(c);
        adjacentCountries.erase(std::remove_if(adjacentCountries.begin(), adjacentCountries.end(), [&](const Country& c) {
			for (auto& country : player.getCountries()) {
                if (country.getName() == c.getName()) {
                    return false;
                }
            }
            return true;
        }), adjacentCountries.end());

		// If the country has no adjacent countries owned by the player, remove from available source countries
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

	// Removing countries that have no adjacent enemy countries or that don't have at least 2 armies
    countries.erase(std::remove_if(countries.begin(), countries.end(), [&](const Country& c) {
        std::vector<Country> adjacentCountries = map.adjacent(c);
		// Removes from adjacentCountries those that the player owns
        adjacentCountries.erase(std::remove_if(adjacentCountries.begin(), adjacentCountries.end(), [&](const Country& c) {
            for (auto& country : player.getCountries()) {
                if (country.getName() == c.getName()) {
                    return true;
                }
            }
            return false;
        }), adjacentCountries.end());

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

std::vector<std::vector<int>> Game::rollingDice(Player& attacker, Player& defender, int nDiceAttacker, int nDiceDefender) {
	std::vector<std::vector<int>> diceResults;

	std::cout << "Rolling dice..." << std::endl;
	std::vector<int> attDiceResults = attacker.getDice().rollDice(nDiceAttacker);
	std::vector<int> defDiceResults = defender.getDice().rollDice(nDiceDefender);

	std::cout << "Comparing dice..." << std::endl;
	std::cout << "Attacker rolled...";
	for (const auto& i : attDiceResults) {
		std::cout << " " << i;
	}
	diceResults.push_back(attDiceResults);
	std::cout << std::endl;

	std::cout << "Defender rolled...";
	for (const auto& i : defDiceResults) {
		std::cout << " " << i;
	}
	diceResults.push_back(defDiceResults);
	std::cout << std::endl;

	return diceResults;
}

void Game::attackPhase(Player& attacker) {
    currentPhase = 2;
    setPhase(currentPhase);

	attacker.executeAttack(&attacker);

	notify();
}

void Game::removeDeadPlayers() {
    std::vector<int> playersIndicesToDelete;
	std::vector<int> turnsIndicesToDelete;
    for (int i = players.size() - 1; i >= 0; --i) {
        const auto player = players[i];
        if (player.getCountries().empty()) {
            playersIndicesToDelete.push_back(i);
        }
    }

	for (int i = turns.size() - 1; i >= 0; --i) {
		const auto player = turns[i];
		if (player.getCountries().empty()) {
			turnsIndicesToDelete.push_back(i);
		}
	}

    for (int i : playersIndicesToDelete) {
        players.erase(players.begin() + i);
    }

	for (int i : turnsIndicesToDelete) {
		turns.erase(turns.begin() + i);
	}
}

Deck Game::getDeck() {
    return deck;
}

std::vector<Country> Game::checkAvailableCountriesToFortifyForCheater(Player& player) {
	std::vector<Country> countries = player.getCountries();

	// Removing countries that have no adjacent enemy countries
	countries.erase(std::remove_if(countries.begin(), countries.end(), [&](const Country& c) {
		std::vector<Country> adjacentCountries = map.adjacent(c);
		// Removes from adjacentCountries those that the player owns
		adjacentCountries.erase(std::remove_if(adjacentCountries.begin(), adjacentCountries.end(), [&](const Country& c) {
			for (auto& country : countries) {
				if (country.getName() == c.getName()) {
					return true;
				}
			}
			return false;
		}), adjacentCountries.end());

		// Cheater fortifies countries that have adjacent enemy countries
		if (adjacentCountries.size() == 0) {
			return true;
		}
		else {
			return false;
		}
	}), countries.end());

	return countries;
}

Player* Game::getCurrentPlayer() const {
	return currentPlayer;
}

int Game::getTurnNumber() const {
	return turnNumber;
}