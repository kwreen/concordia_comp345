#include <cstdlib> // Let it be known that I, Alessandro, strongly disprove of this method.
#include <ctime>
#include "Deck.h"

int Deck::nExchanges = 0;

Card Deck::draw(Player& player) {
	std::srand(std::time(0));
	int randIndex = std::rand() % cards.size();
	Card card = cards[randIndex];

	player.getHand().add(card);
	cards.erase(cards.begin() + randIndex);
	return card;
}

int Deck::getNExchanges() {
	return nExchanges;
}

void Deck::incNExchanges() {
	++nExchanges;
}
