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
	cSize = 0;

}
void Map::addCountry(string name, string continent)
{

	adjList.push_back(Country(name,NULL));
	//cout << "Added " << name << endl;
	int cIndex = getIndexContinent(continent);
	//cout << cIndex << endl;

	if (cIndex < 0) // if the continent doesnt exist yet..add it
	{
		//cout << "Entered for " << name << endl;
		continentList.push_back(Continent(continent));
		cSize++;
	}
	else // if it exists update country to point to its continent.
	{

		//cout << adjList.size()<< endl;
		adjList[adjList.size()].parent = Continent(continent);

	}
	size++;

}
void Map::addAdjacent(Country a, Country b) // add country a is ajacent to countryb
{
	int x = getIndex(a.getName());
	int y = getIndex(b.getName());
	// gotta add it to both's adjcountryList
	adjList[x].adjCountryList = new Node(y,adjList[x].adjCountryList);
	adjList[y].adjCountryList = new Node(x,adjList[y].adjCountryList);

}


void Map::showAdjacent(Country a)
{
	Node *current = new Node;
	int x = getIndex(a.getName());
	current = adjList[x].adjCountryList;
	cout << a.getName() << " is adjacent to the following countries: " << endl;
	while (current != NULL)
	{
		int temp = current->getIndex();
		cout << adjList[temp].getName() << endl;
		current = current->next;
	}
}
void Map::printCountries()
{
	for (int i=0;i<size;i++)
	{
		cout << adjList[i].getName() << endl;
	}
}
void Map::printContinents()
{
	for (int i=0;i<cSize;i++)
	{
		cout << continentList[i].getName() << endl;
	}
}
int Map::getIndex(string name) // for countries
{
	for (int i=0; i < size;i++)
	{
		if (adjList[i].getName() == name)
			return i;
	}
	return -1; // not found.
}
int Map::getIndexContinent(string continent)
{
	for (int i=0; i<cSize;i++)
	{
		if (continentList[i].getName() == continent)
		{
			return i;
		}
	}
	return -1; // not found
}
int Map::getSize()
{
	return size;
}
int main()
{
	Map map;
	Continent conA("North America");
	Country a("Canada",conA);
	Country b("Toronto",conA);
	//cout << a.getContinent() << endl;

	map.addCountry("Canada","North America");
	map.addCountry("Toronto","North America");
	//cout << map.getIndex("United States") << endl;
	map.addAdjacent(a,b);
	//map.addAdjacent(a,c);
	map.showAdjacent(a);
	cout << "Printing Countries" << endl;
	map.printCountries();
	cout << "Printing Continents" << endl;
	map.printContinents();
	return 0;
}
