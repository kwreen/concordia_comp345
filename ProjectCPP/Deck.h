#pragma once

#include "Card.h"
#include "Player.h"
#include "Country.h"
#include <vector>

class Deck {
	private:
		std::vector<Card> cards; //the deck of cards

		static int nExchanges; //# of exchanges

	public:
		Deck() = default;

		Deck(const std::vector<Card>& cards) : cards(cards) {} //<--- purpose of this? 	Give it a vector of cards to be used as a deck, so we are giving it the deck?

		Card draw(Player& player);

		int nCards() const;

		void loadDeck(const std::vector<Country>& countries);

		static int getNExchanges();

		static void incNExchanges();
};
