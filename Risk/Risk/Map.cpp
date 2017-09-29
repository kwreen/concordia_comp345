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

