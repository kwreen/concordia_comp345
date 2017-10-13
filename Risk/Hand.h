#pragma once

#include "Card.h"
#include <vector>

class Hand {
	private:
		std::vector<Card> cards;

		static int getArmies();

	public:
		Hand() = default;

		Hand(const std::vector<Card>& cards) : cards(cards) {}

		std::vector<Card> getCards() const;

		void add(const Card& card);

		int exchange(const Card& card0, const Card& card1, const Card& card2);
};
