/*
 * Driver.cpp
 *
 *  Created on: Sep 22, 2017
 *      Author: Jordan
 */

#include "Deck.h"
#include <iostream>
#include <string>
#include<typeinfo> //used to get type of card
#include "Hand.h"
using namespace std;
int main()
{

	Deck d1(12); //deck has to be multiples of 3(even amount of cards), cannot use
    d1.shuffle(); //always needs to be called before getting the deck
    cout<<"Printing deck from main\n";
    d1.getCurrentDeck();

   /* CardTypes** s = d1.getDeck();

    for(int i=0;i<d1.getDeckSize();i++)
    {
    	cout<<s[i]->getCard();
    }
    */

/*
    Make sure not to use this with fillhand as it does same thing as fillhand. Uncomment this comment fillhand and it works. Use fillhand and it doesn't
    cout<<"Drawing in main:\n";
    for(int i=0;i<6;i++)
    {
    CardTypes* card = d1.draw();
    cout<<"Card:"<<card->getCard() <<"\n";
    }
    */
  //  d1.getCurrentDeck();
   //d1.shuffle();
  //  d1.getCurrentDeck();
    Hand myHand(d1);
   myHand.fillHand(7);
//  myHand.getHand();









}

