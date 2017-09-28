#pragma once

#include "Country.h"
#include <string>
#include <unordered_map>
#include <vector>

class Map {
	private:
		std::vector<Country> countries;
		std::vector<std::vector<bool>> adjacencyMatrix;
		// continents is a map between strings (representing the continent name) and a vector of ints (representing the indices into countries).
		std::unordered_map<std::string, std::vector<int>> continents;

	public:
		std::vector<Country> getContinent(const std::string& continentName) const;

		bool loadMap(const std::string& filename);
};
