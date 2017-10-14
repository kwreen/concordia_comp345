/*
 * Hand.cpp
 *
 *  Created on: Sep 25, 2017
 *      Author: Jordan
 */
#include "Hand.h"
#include <iostream>
using namespace std;


Hand::Hand(Deck d)
{
	cout<<"Printing from Constructor\n";
	myDeck  = &d;
	myDeck->getCurrentDeck(); //it is grabbing right deck

	cards = new CardTypes*[d.getDeckSize()];
}
void Hand::fillHand(int num)
{
	//CardTypes** deck = myDeck->getDeck(); //pointer to deck(not needed)
	if(num > myDeck->getDeckSize())
	{
		cout<<"You cannot draw more cards then there are in deck\n";
		exit(0);
	}
	cout<<"Drawing in class\n";
	for(int i=0;i<num;i++)
	{
		CardTypes* myCards = myDeck->draw();
		cout<<myCards->getCard()<<"\n"; //for testing purposes, printing incorrect set of cards
		//cards[i] = myCards;//copy card to hand array
		handSize++;
	}
}
void Hand::getHand()
{
	cout<<"Current Hand\n";
	cout<<"---------------\n";
	for(int i=0;i<handSize;i++)
	{
		cout<<cards[i]->getCard()<<"\n";
	}
}
int Hand::getHandSize()
{
	return handSize;
}
int Hand::exchange() //for now this just returns number of armies,no object returned
{
	/* How this works:
	 * if have 3 of each type in hand or 3 of same time u get 5 armies,this happens again another 5 etc
	 */
	int infantryCounter = 0;
	int artilleryCounter=0;
	int cavalryCounter=0;
	for(int i=0;i<handSize;i++)
	{
		string card = cards[i]->getCard();
		if (card == "Infantry")
		{
			infantryCounter++;
		}
		else if(card == "Artillery")
		{
			artilleryCounter++;
		}
		else
		{
			cavalryCounter++;
		}
	}
	if(infantryCounter >=3 || artilleryCounter >=3 || cavalryCounter >=3 || ((infantryCounter>=1) && (artilleryCounter>=1) && (cavalryCounter>=1))) //3 or more of each card in deck
	{
		armies+=5;
		return armies;
	}
	else
	{
		return armies;
	}

}




