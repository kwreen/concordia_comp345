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
	void addCountry(std::string name);
	void Map::addAdjacent(Country a, Country b)
	void getCountries();
	int getSize();

private:
	std::vector<Country> adjList;
	int size;

};




#endif /* MAP_H_ */
