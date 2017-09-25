#pragma once
#include <vector>;

using std::vector;

class Player {
private:
	// vector<Country> countries;
	// Deck deck;
	// Deck hand;
	// DiceFacility diceFacility

public:
	Player();
	// Player(vector<Country> countries, Deck deck, DiceFacility diceFacility);
	// inline vector<Country> getCountries() const;
	// inline Deck getDeck() const;
	// inline Deck getHand() const;
	// inline DiceFacility getDiceFacility() const;
	void reinforce();
	void attack();
	void fortify();

private:
	// void setCountries(vector<Country> countries);
	// void setDeck(Deck deck);
	// void setHand(Deck deck);
	// void setDiceFcility(DiceFacility diceFacility);
};