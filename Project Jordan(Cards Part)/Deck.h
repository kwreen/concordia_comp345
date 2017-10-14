/*
 * Deck.h
 *
 *  Created on: Sep 22, 2017
 *      Author: Jordan
 */

#ifndef DECK_H_
#define DECK_H_
#include "CardTypes.h"
class Deck
{

	int deckSize;
	CardTypes* p[12];//initial array which pointers to different subclass objects(the cardtypes)
	CardTypes* s[12];//randomaly cards placed in this deck(takes from p)
	int seed;//used for random # generation
public:
	Deck(int size);
	//~Deck(); //to free up memory,destructor(to be used with ~CardTypes() for clearing up heap
	void shuffle(); //shuffles the cards in deck so not same setup each time
	CardTypes** getDeck(); //returns a pointer to a pointer array of cardtypes(the deck). After every shuffle you will have a new deck
	int getDeckSize();
	void getCurrentDeck(); //returns the currentdeck format as a string
	CardTypes* draw();//draws a card from the end of s(this will constitute the top of the deck)

};
#endif /* DECK_H_ */
