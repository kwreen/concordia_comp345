#pragma once

#include "Map.h"
#include "Subject.h"
#include "Deck.h"
#include "Country.h"
#include <vector>

class Player;

class Game : public Subject {

private:
	Deck deck;
	static Map map;
	std::vector<Player> players;
	static std::vector<Player> turns;
	int numPlayers;
    int currentPhase;
	void setGameMap(const std::string& mapName);
	void createPlayers(int nPlayers);
	void assignTurns();
	void startUp();
	void assignArmies();
	void assignObservers();

public:
	Game(const std::string& mapName, int nPlayers);
	Game(const std::string& mapName, const std::vector<Player>& players);
	std::vector<Player>& getTurns();
	std::vector<Player> getUnorderedPlayers() { return players;}
	void reinforcementPhase(Player& player);
	void fortificationPhase(Player& player);
	Map getMap() const;
	static Player& getOwner(const Country& country);
	static int getArmiesToAdd(const Player& player);
	static std::vector<Country> checkAvailableSourceCountriesToFortify(Player& player);
	static std::vector<Country> checkAvailableTargetCountriesToFortify(Player& player, Country source);
	static std::vector<Country> checkAvailableAttackingCountriesToAttack(Player& player);
	static std::vector<Country> checkAvailableDefendingCountriesToAttack(Player& player, Country source);
	static std::vector<Country> checkAvailableCountriesToFortifyForCheater(Player& player);
	static std::vector<std::vector<int>> rollingDice(Player& attacker, Player& defender, int nDiceAttacker, int nDiceDefender);
	void attackPhase(Player& player);
	void removeDeadPlayers();
	Deck getDeck();
};
