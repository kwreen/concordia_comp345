/*
 * country.cpp
 *
 *  Created on: Sep 26, 2017
 *      Author: johnb
 */
#include "country.h"

using namespace std;
Country::Country()
{

}
Country::Country(string n, Node* cList)
{
	name = n;
	adjCountryList = cList;
}
Country::Country(string n, Continent p)
{
	name = n;
	parent = p;
}
Country::Country(string n, Node *cList, Continent p)
{
	name = n;
	adjCountryList = cList;
	parent = p;
}
string Country::getName()
{
	return name;
}

string Country::getContinent()
{
	return parent.getName();
}
/*
void Country::setParent(Node* p)
{
	parent = p;
}
*/



