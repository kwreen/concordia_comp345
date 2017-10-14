/*
 * Hand.h
 *
 *  Created on: Sep 25, 2017
 *      Author: Jordan
 */

#ifndef HAND_H_
#define HAND_H_

#include "Deck.h"

class Hand
{
private:
Deck *myDeck;
CardTypes** cards;
int handSize = 0;
int armies = 0;//start army return at 5
public:
	Hand(Deck deck);
	void fillHand(int draw); //puts "draw" amount of cards in hand, continiously draws cards = draw
	int exchange();
	void getHand();
	int getHandSize();
};




#endif /* HAND_H_ */
