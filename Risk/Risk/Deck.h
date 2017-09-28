#pragma once

#include "Card.h"
#include "Player.h"
#include <vector>

class Deck {
	private:
		std::vector<Card> cards;

		static int nExchanges;

	public:
		Deck(const std::vector<Card>& cards) : cards(cards) {}

		Card draw(Player& player);

		static int getNExchanges();

		static void incNExchanges();
};
