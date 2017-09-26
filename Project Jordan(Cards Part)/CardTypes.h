/*
 * CardTypes.h
 *
 *  Created on: Sep 22, 2017
 *      Author: Jordan
 */

#ifndef CARDTYPES_H_
#define CARDTYPES_H_

#include <string>
using namespace std;
class CardTypes //empty contained for now just so we can use inheritence to store different objects in array in Deck.cpp
{
public:
	virtual string getCard() = 0;
	//virtual ~CardTypes() {}; //will be used to clear deck array,right now pointers on heap remain(see Deck.cpp)
};
class Infantry: public CardTypes
{
	const string name = "Infantry";
	public:
	string getCard();
};
class Artillery:public CardTypes //: used for inhertience in c++ so Artillery extends CardTypes
{
	const string name= "Artillery";
    public:
	string getCard();
};
class Cavalry:public CardTypes
{
	const string name = "Cavalry";
    public:
	string getCard();
};



#endif /* CARDTYPES_H_ */
