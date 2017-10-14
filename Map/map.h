/*
 * map.h
 *
 *  Created on: Sep 26, 2017
 *      Author: johnb
 */

#ifndef MAP_H_
#define MAP_H_
#include "country.h"
#include <vector>
class Map
{
public:
	Map();
	void addCountry(std::string name, std::string continent);
	int getIndex(std::string name);
	int getIndexContinent(std::string continent);
	void addAdjacent(Country a, Country b);
	void showAdjacent(Country a);
	void printCountries();
	void printContinents();
	int getSize();


private:
	std::vector<Country> adjList; // used for countries adjacency
	std::vector<Continent> continentList; // used for continents
	int size; // for countries.
	int cSize; // for continents

};




#endif /* MAP_H_ */
