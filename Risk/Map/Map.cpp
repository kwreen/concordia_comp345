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

	adjList.push_back(Country(name, NULL));
	size++;

}

void Map::addAdjacent(Country a, Country b) // add country a is ajacent to countryb
{
	int x = getIndex(a.getName());
	int y = getIndex(b.getName());
	// gotta add it to both's adjcountryList
	adjList[x].adjCountryList = new Node(y, adjList[x].adjCountryList);
	adjList[y].adjCountryList = new Node(x, adjList[y].adjCountryList);
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

void Map::getCountries()
{
	for (int i = 0; i<size; i++)
	{
		cout << adjList[i].getName() << endl;
	}
}

int Map::getIndex(string name)
{
	for (int i = 0; i < size; i++)
	{
		if (adjList[i].getName() == name)
			return i;
	}
	return -1; // not found.
}

int Map::getSize()
{
	return size;
}
