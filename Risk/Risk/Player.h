#pragma once
#include <vector>;
#include "Dice.h"
#include "Country.h"
#include "Deck.h"
#include "Hand.h"

using std::vector;

class Player {
	private:
		 vector<Country> _countries;
		 Hand _hand;
		 Dice _dice;

	public:
		Player(vector<Country> countries, Hand hand, Dice dice);
		inline vector<Country>& getCountries() const;
		inline Hand getHand() const;
		inline Dice getDice() const;
		void reinforce();
		void attack();
		void fortify();

	private:
		 void setCountries(vector<Country> countries);
		 void setHand(Hand hand);
		 void setDice(Dice dice);
};