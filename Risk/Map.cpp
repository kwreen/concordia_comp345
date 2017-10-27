#include "Map.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

std::vector<Country> Map::getCountries() const {
	return countries;
}

std::vector<std::vector<bool>> Map::getAdjacencyMatrix() const {
	return adjacencyMatrix;
}

std::vector<Country> Map::getContinent(const std::string& continentName) const {
	const std::vector<int> indices = continents.at(continentName);
	std::vector<Country> names;
	for (int index : indices) {
		names.push_back(countries[index]);
	}

	return names;
}

int Map::getContinentValue(const std::string& continentName) const {
	return continentValues.find(continentName)->second;
}

std::vector<std::string> Map::getContinentNames() const {
	std::vector<std::string> continentNames;
	for (const auto& kv : continents) {
		continentNames.push_back(kv.first);
	}

	return continentNames;
}

std::vector<Country> Map::adjacent(const Country& country) const {
	std::vector<Country> adjacentCountries;
	// Find index of the specified country.
	int countryIndex;
	for (countryIndex = 0; countryIndex < countries.size(); ++countryIndex) {
		if (country == countries[countryIndex]) break;
	}

	// Get row of the adjacency matrix.
	std::vector<bool> indices = adjacencyMatrix[countryIndex];

	// Iterate over this row. Every time a true value is encountered, push the country onto the vector.
	for (int i = 0; i < indices.size(); ++i) {
		if (indices[i]) {
			adjacentCountries.push_back(countries[i]);
		}
	}

	return adjacentCountries;
}

std::vector<Country>
Map::adjacentInContinent(const Country& country, const std::string& continent) const {
	std::vector<Country> adjacentCountries;
	// Find index of the specified country.
	int countryIndex;
	for (countryIndex = 0; countryIndex < countries.size(); ++countryIndex) {
		if (country == countries[countryIndex]) break;
	}

	// Get row of the adjacency matrix.
	std::vector<bool> indices = adjacencyMatrix[countryIndex];

	// Iterate over this row. Every time a true value is encountered, push the country onto the vector.
	for (int i = 0; i < indices.size(); ++i) {
		if (indices[i]) {
			auto continentIndices = continents.at(continent);
			// Check to make sure the index i is in continentIndices before adding the country.
			for (int continentIndex : continentIndices) {
				if (continentIndex == i) {
					adjacentCountries.push_back(countries[i]);
					break;
				}
			}
		}
	}

	return adjacentCountries;
}

std::vector<std::string> Map::continentsOwned(const Player& player) const {
	std::vector<std::string> continentsOwned;
	const std::vector<Country>& playerCountries = player.getCountries();
	std::vector<int> playerCountryIndices;

	// Add country indice from the player's countries if the player owns the country
	for (int i = 0; i < countries.size(); ++i) {
		const auto Country = countries[i];
		if (std::find(playerCountries.begin(), playerCountries.end(), Country) != playerCountries.end()) {
			playerCountryIndices.push_back(i);
		}
	}

	// Add continent name to continentsOwned if player owns all countries in the continent
	for (const auto& kv : continents) {
		const auto continentName = kv.first;
		const auto& continentIndices = kv.second;

		if (std::is_permutation(playerCountryIndices.begin(), playerCountryIndices.end(), continentIndices.begin(), continentIndices.end())) {
			continentsOwned.push_back(kv.first);
		}
	}

	return continentsOwned;
}

void Map::print() const {
	std::cout << "Territories:\n";
	for (int i = 0; i < countries.size(); ++i) {
		std::cout << i << ' ' << countries[i].getName() << std::endl;
	}

	std::cout << std::endl;

	std::cout << "Adjacency Matrix:\n";
	for (int row = 0; row < adjacencyMatrix.size(); ++row) {
		for (int col = 0; col < adjacencyMatrix.size(); ++col) {
			std::cout << adjacencyMatrix[row][col] << ' ';
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;

	std::cout << "Continents:\n";
	for (const auto& kv : continents) {
		std::cout << kv.first << ": ";
		std::vector<int> indices = kv.second;
		for (int index : indices) {
			std::cout << countries[index].getName() << ' ';
		}
		std::cout << std::endl;
	}
}

