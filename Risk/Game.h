#pragma once

#include "Map.h"
#include "Player.h"
#include "Subject.h"
#include "Deck.h"
#include "Country.h"
#include <vector>

class Game {

private:
	Deck deck;
	Map map;
	Subject s; //to use observer pattern
	std::vector<Player> players;
	std::vector<Player> turns;
	int numPlayers;

	Player getOwner(const Country& country) const;
	void setGameMap(const std::string& mapName);
	void createPlayers(int nPlayers);
	void assignTurns();
	void startUp();
	void assignArmies();

	int getArmiesToAdd(const Player& player) const;
	void assignObservers(vector<Player>& p); //adds players to observers list

public:
	Game(const std::string& mapName, int nPlayers);
	vector<Player> getTurns();
	vector<Player> getObservers();
	void printObservers();
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
