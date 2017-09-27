/*
* country.h
*
*  Created on: Sep 26, 2017
*      Author: johnb
*/

#ifndef COUNTRY_H_
#define COUNTRY_H_

#include "node.h"
#include <string>
class Country
{
private:
	std::string parent; // use this for continents.
	std::string name;


public:
	Node* adjCountryList; // countries that are adjacent to each other.
	Country();
	Country(std::string n);
	Country(std::string n, std::string p);
	Country(std::string n, Node* cList);
	std::string getName();
	std::string getContinent();
	void setParent(std::string p);


};



#endif /* COUNTRY_H_ */
