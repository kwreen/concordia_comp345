#include <cstdlib>
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

int Deck::nCards() const {
	return cards.size();
}

void Deck::loadDeck(const std::vector<Country>& countries) {
	for (int i = 0; i < countries.size(); ++i) {
		CardType cardType = CardType(i % 3);
		Country country = countries[i];
		cards.push_back(Card(country, cardType));
	}
}

int Deck::getNExchanges() {
	return nExchanges;
}

void Deck::incNExchanges() {
	++nExchanges;
}