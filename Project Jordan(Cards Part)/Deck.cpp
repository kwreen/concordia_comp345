/*
 * Deck.cpp
 *
 *  Created on: Sep 22, 2017
 *      Author: Jordan
 */

#include "Deck.h"
#include <stdlib.h> //c file for random number generator
#include <iostream>
using namespace std;


Deck::Deck(int size) //define size of deck
{
	if(size%3 !=0)//make sure 3 of each type is in deck(even amount of cards as per instructions)
	{
		cout<<"Invalid deck,must have even amount of cards\n";
		exit(0);
	}
	deckSize = size;
	seed = rand()%100;
	srand(seed);
	//populate deck with card types
	//create card objects, 12 of them so 4 of each type
	for(int i=0;i<deckSize;i+=3)
	{
		p[i]= new Infantry(); //holder object to be placed in s randomly
		p[i+1] = new Artillery();
		p[i+2] = new Cavalry();

	}
}
int Deck::getDeckSize()
{
	return deckSize;
}
void Deck::shuffle()
{
	//note have to change logic if any size
	int j = 0;
	int k = 1;
	int l = 2; //initial setup
	int n = rand()%3 + 1; //gives random # between 1 and 3 1=infantry,2 = artillery,3 = cavalry
	int i=0;
    while(i<deckSize)
    {
    	 n = rand()%3+1;
    	if(n==1)
    	{
    		if(j>deckSize-1) //means no more infantry cards
    		{
    			continue; //used to reset loop foranother iteration
    		}
    		else
    		{
    		s[i] = p[j];
    		j+=3;
    		i++;
    		}
    	}
    	else if(n==2)
    	{
    		if(k>deckSize-1)//means no Artillery cards
    		{
    			continue;
    		}
    		else
    		{
    			s[i] = p[k];
    			k+=3;
    			i++;
    		}
    	}
    	else
    	{
    		if(l>deckSize-1) //means no more cavalary cards
    		{
    			continue;
    		}
    		else
    		{
    			s[i] = p[l];
    			l+=3;
    			i++;
    		}
    	}
    }

}
CardTypes** Deck::getDeck() //returns pointer to a pointer (s)
{
	return s;
}
void Deck::getCurrentDeck() //returns just the data
{
	cout<<"Deck\n";
	cout<<"____\n";
	for(int i=0;i<deckSize;i++)
	{
		cout<<s[i]->getCard()<<"\n";

	}
}
CardTypes* Deck::draw() //draws a card from the deck and returns it
{
	if(deckSize == 0)
	{
		cout<<"The deck is empty,cannot draw a card, returning null";
		return NULL;
	}
	CardTypes* card = s[deckSize-1];

	//delete s[deckSize-1];//clear heap
	//s[deckSize-1] = NULL;//remove what pointer was pointing too (as card has been drawn)
	deckSize--;
	return card;

}

/*Deck::~Deck()
{
	delete [] p;
	delete [] s;
}
*/







