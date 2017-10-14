/*
 * continent.cpp
 *
 *  Created on: Sep 27, 2017
 *      Author: johnb
 */
#include "continent.h"
#include <string>
using namespace std;

Continent::Continent()
{

}
Continent::Continent(string cName)
{
	name = cName;
}
string Continent::getName()
{
	return name;

}



