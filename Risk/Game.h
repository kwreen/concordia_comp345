#pragma once

#include "Map.h"
#include "Player.h"
#include "Subject.h"
#include "Deck.h"
#include "Country.h"
#include <vector>

class Game : public Subject {

private:
	Deck deck;
	Map map;
	std::vector<Player> players;
	std::vector<Player> turns;
	int numPlayers;
    int currentPhase;
	Player getOwner(const Country& country) const;
	void setGameMap(const std::string& mapName);
	void createPlayers(int nPlayers);
	void assignTurns();
	void startUp();
	void assignArmies();
	int getArmiesToAdd(const Player& player) const;
	void assignObservers();

public:
	Game(const std::string& mapName, int nPlayers);
	vector<Player> getTurns();
	vector<Player> getUnorderedPlayers() { return players;}
	void reinforcementPhase(Player& player);
	void fortificationPhase(Player& player);
	Map getMap() const;
	vector<Country> checkAvailableCountriesToFortify(Player& player);
	vector<Country> checkAvailableCountriesToAttack(Player& player);
	void attackPhase(Player& player);
	void removeDeadPlayers();
	Deck getDeck();
};
