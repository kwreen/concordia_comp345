#pragma once
#include <vector>
#include <string>
#include "DiceFacility.h"
#include "Country.h"
#include "Hand.h"
#include "HumanPlayer.h"

class Strategy;

class Player {
private:
	Strategy *strategy;
	std::vector<Country> _countries;
	Hand _hand;
	DiceFacility _dice;
	int player = 0;
	int armies = 0;

public:
	Player() = default;
	Player(std::vector<Country> countries, Hand hand, DiceFacility dice, int playerNumber, Strategy *strategy);
	Player(int playerNumber);
	std::vector<Country>& getCountries();
	const std::vector<Country>& getCountries() const;
	Hand& getHand();
	const Hand& getHand() const;
	DiceFacility getDice() const;
	std::string getID();
	int getIDAsInt() const;
	void assignCountry(Country c);
	int amtCountries();
	void initializeArmies();
	int getPlayerArmies();
	void setArmies(int nArmies);
	void printCountries();

    // Strategy pattern
    void setStrategy(Strategy *strategy);
	void executeReinforcement(Player* player);
	void executeAttack(Player* player);
	void executeFortify(Player* player);

private:
	void setCountries(std::vector<Country> countries);
	void setHand(Hand hand);
	void setDice(DiceFacility dice);
};
