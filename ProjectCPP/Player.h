#pragma once
#include <vector>
#include "DiceRollingFacility.h"
#include "Country.h"
#include "Hand.h"
#include <string>
using namespace std;

using std::vector;

class Player {
	private:
		 vector<Country> _countries;
		 Hand _hand;
		 DiceFacility _dice;
		 int player; //give each player a player id so can differentiate each
		 int armies=0;

	public:
		Player() = default;
		Player(vector<Country> countries, Hand hand, DiceFacility dice,int playerNumber);
		Player(int playerNumber);
		vector<Country> getCountries();
		Hand& getHand();
		DiceFacility getDice() const;
		string playerAsString();  //will return string representation of player object
		void assignCountry(Country c);
		int amtCountries(); //returns amount of countries player has
		void increasePlayerArmies();
		void countryArmies(); //places armies on countries
		int getPlayerArmies();
		void countries(); //prints country list
		void reinforce();
		void attack();
		void fortify();
		//will need to add a getPlayerArmies() here which adds getArmies() from hand + ones on countries

	private:
		 void setCountries(vector<Country> countries);
		 void setHand(Hand hand);
		 void setDice(DiceFacility dice);
};
