#pragma once
#include <vector>
#include "DiceFacility.h"
#include "Country.h"
#include "Hand.h"

using std::vector;

class Player {
	private:
		 vector<Country> _countries;
		 Hand _hand;
		 DiceFacility _dice;

	public:
		Player() = default;
		Player(vector<Country> countries, Hand hand, DiceFacility dice);
		vector<Country>& getCountries() const;
		Hand& getHand();
		DiceFacility getDice() const;
		void reinforce();
		void attack();
		void fortify();

	private:
		 void setCountries(vector<Country> countries);
		 void setHand(Hand hand);
		 void setDice(DiceFacility dice);
};