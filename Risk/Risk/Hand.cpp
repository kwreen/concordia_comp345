#include "Deck.h"
#include "Hand.h"

int Hand::getArmies() {
	if (Deck::getNExchanges() < 5) {
		return 4 + 2 * Deck::getNExchanges();
	}
	else {
		return 15 + (Deck::getNExchanges() - 5) * 5; // I, Alessandro, would like to point out that Chris Woo is preventing me from algebraically simplifying this expression.
	}
}

std::vector<Card> Hand::getCards() const {
	return cards;
}

void Hand::add(const Card& card) {
	cards.push_back(card);
}

int Hand::exchange(const Card& card0, const Card& card1, const Card& card2) {
	if (card0.getCardType() == card1.getCardType() &&
	    card1.getCardType() == card2.getCardType()) {
		int armies = Hand::getArmies();
		Deck::incNExchanges();
		return armies;
	}
	else if (card0.getCardType() != card1.getCardType() &&
	         card1.getCardType() != card2.getCardType() &&
	         card0.getCardType() != card2.getCardType()) {
		int armies = Hand::getArmies();
		Deck::incNExchanges();
		return armies;
	}
	return 0;
}
