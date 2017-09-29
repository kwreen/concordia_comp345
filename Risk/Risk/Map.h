#pragma once

#include "Country.h"
#include "MapLoader.h"
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
		std::vector<Country> getCountries() const;

		std::vector<std::vector<bool>> getAdjacencyMatrix() const;

		std::vector<Country> getContinent(const std::string& continentName) const;

		std::vector<Country> adjacent(const Country& country) const;

		friend Map MapLoader::loadMap(std::string filename);

		void print() const;
};
