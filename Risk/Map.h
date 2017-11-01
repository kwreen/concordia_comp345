#pragma once

#include "Country.h"
#include "MapLoader.h"
#include "Player.h"
#include <string>
#include <unordered_map>
#include <vector>

class Map {
private:
	std::vector<Country> countries;
	std::vector<std::vector<bool>> adjacencyMatrix;
	// continents is a map between strings (representing the continent name) and a vector of ints (representing the indices into countries).
	std::unordered_map<std::string, std::vector<int>> continents;
	// continentValues is a map between strings (for continent names) and their values.
	std::unordered_map<std::string, int> continentValues;

public:
	std::vector<Country> getCountries() const;

	std::vector<std::vector<bool>> getAdjacencyMatrix() const;

	std::vector<Country> getContinent(const std::string& continentName) const;

	int getContinentValue(const std::string& continentName) const;

	std::vector<std::string> getContinentNames() const;

	std::vector<Country> adjacent(const Country& country) const;

	std::vector<Country>
	adjacentInContinent(const Country& country, const std::string& continent) const;

	std::vector<std::string> continentsOwned(const Player& player) const;

	void print() const;

	friend Map MapLoader::loadMap(std::string filename);
};
