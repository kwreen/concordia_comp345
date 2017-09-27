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
Country::Country(string n, Node* clist)
{
	name = n;
	adjCountryList = clist;
}
Country::Country(string n)
{
	name = n;
}
string Country::getName()
{
	return name;
}
string Country::getContinent()
{
	return parent;
}




