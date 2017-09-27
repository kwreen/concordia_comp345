/*
 * map.cpp
 *
 *  Created on: Sep 26, 2017
 *      Author: johnb
 */
#include "map.h"
#include <string>
using namespace std;
Map::Map()
{
	size = 0;

}
void Map::addCountry(string name)
{
	adjList.push_back(Country(name));
	size++;

}
void Map::addAdjacent(Country a, Country b) // add country a is ajacent to countryb
{

// not sure... what to write here

}
void Map::getCountries()
{
	for (int i=0;i<size;i++)
	{
		cout << adjList[i].getName() << endl;
	}
}
int Map::getSize()
{
	return size;
}
int main()
{
	Map map;

	map.addCountry("Canada");
	map.addCountry("United States");
	map.addCountry("test");
	cout << map.getSize() << endl;
	map.getCountries();
	return 0;
}
