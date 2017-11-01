#pragma once

#include "Card.h"
#include <vector>

class Hand {
	private:
		std::vector<Card> cards; //stores cards/a hand for a player

		static int getArmies();

	public:
		Hand() = default; //not needed just means default constructor

		Hand(const std::vector<Card>& cards) : cards(cards) {}

		std::vector<Card> getCards() const; //returns hand array

		void add(const Card& card); //adds a card to hand(should be using draw from deck

		int exchange(const Card& card0, const Card& card1, const Card& card2);//exchange for armies
};
