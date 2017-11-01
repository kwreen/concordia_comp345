#include <cstdlib>
#include <ctime>
#include "Deck.h"

int Deck::nExchanges = 0; //this could have been assigned in header file

Card Deck::draw(Player& player) { //this is supposed to be used in hand
	//no type check to see if deck is empty
	std::srand(std::time(0));//<-- seed
	int randIndex = std::rand() % cards.size(); //random index between 0 and size of deck -1. This is called everytime so if 6 cards in deck index 0 to 5 then 0-4 etc will always be an index
	Card card = cards[randIndex]; //<--loadDeck must be called first, this should be put in constructor then. Grabs a card at random index

	player.getHand().add(card); //gets hand object for player and adds a card to his/her hand.
	cards.erase(cards.begin() + randIndex); //Erases card at the index pushes all left
	return card;
}

int Deck::nCards() const { //returns size of deck
	return cards.size();
}

void Deck::loadDeck(const std::vector<Country>& countries) { //creates deck given a vector of countries?
	for (int i = 0; i < countries.size(); ++i) {
		CardType cardType = CardType(i % 3); //gets from the enum at a random index.Anyone can grade it as it isn't part of any class
		Country country = countries[i]; //grabs country from vector
		cards.push_back(Card(country, cardType));//puts country,cardtype in deck(not sure why country is needed)This may definitetly not be even
	}
}

int Deck::getNExchanges() { //returns number of exchanges
	return nExchanges;
}

void Deck::incNExchanges() { //increments the amount of exchanges
	++nExchanges;
}



