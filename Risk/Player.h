#pragma once
#include <vector>
#include "DiceFacility.h"
#include "Country.h"
#include "Hand.h"
#include "Observer.h"
#include <string>
using namespace std;

using std::vector;

class Player : public Observer {
private:
	vector<Country> _countries;
	Hand _hand;
	DiceFacility _dice;
	int player = 0; //give each player a player id so can differentiate each
	int armies = 0;

public:
	Player() = default;
	Player(vector<Country> countries, Hand hand, DiceFacility dice, int playerNumber);
	Player(int playerNumber);
	vector<Country>& getCountries();
	const vector<Country>& getCountries() const;
	Hand& getHand();
	const Hand& getHand() const;
	DiceFacility getDice() const;
	string getID();  //will return string representation of player object
	int getIDAsInt(); // returns strictly the player id this will be used to see if a player array index is empty
	void assignCountry(Country c);
	int amtCountries(); //returns amount of countries player has
	void increasePlayerArmies();
	void initializeArmies(); //places armies on countries
	int getPlayerArmies();
	void setArmies(int nArmies);
	void printCountries(); //prints country list
	void reinforce();
	void attack();
	void fortify(int nArmies, Country& source, Country& target);
	// Observer pattern
	void showStats();
	void update();

private:
	void setCountries(vector<Country> countries);
	void setHand(Hand hand);
	void setDice(DiceFacility dice);
};
