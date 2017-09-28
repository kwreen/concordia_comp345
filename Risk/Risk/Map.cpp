#include "Map.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

// Let it be known that Chris does not want me to put this in an anonymous namespace.
std::vector<std::string> split(const std::string& input, char delim) {
	std::stringstream ss(input);
	std::string segment;
	std::vector<std::string> contents;
	while (std::getline(ss, segment, delim)) {
		contents.push_back(segment);
	}
	return contents;
}

std::vector<Country> Map::getContinent(const std::string& continentName) const {
	const std::vector<int> indices = continents.at(continentName);
	std::vector<Country> names;
	for (int index : indices) {
		names.push_back(countries[index]);
	}

	return names;
}

bool Map::loadMap(const std::string& filename) {
	std::ifstream ifs(filename);
	std::string line;

	// Get the continents.
	while (std::getline(ifs, line) && line != "[Continents]") {}
	while (std::getline(ifs, line) && line != "") {
		const int equalsIndex = line.find('=');
		const std::string continent = line.substr(equalsIndex);
		continents.insert({ continent, std::vector<int>() });
	}

	// Get all the territories.
	while (std::getline(ifs, line) && line != "[Territories]") {}
	while (std::getline(ifs, line)) {
		// Get the territory name.
		if (line != "") {
			const int commaIndex = line.find(',');
			const std::string countryName = line.substr(commaIndex);
			// Confirm that country is unique.
			if (std::find(countries.begin(), countries.end(), countryName) != countries.end()) {
				std::cerr << "Duplicate territory detected: " << countryName << std::endl;
				return false;
			}
			countries.push_back(countryName);
		}
	}

	// Re-read file.
	ifs.clear();
	ifs.seekg(0, ifs.beg);

	// Initialize the adjacency matrix.
	adjacencyMatrix.resize(countries.size(), std::vector<bool>(countries.size()));

	// Set adjacencyMatrix and continents territory by territory.
	while (std::getline(ifs, line) && line != "[Territories]") {}
	while (std::getline(ifs, line)) {
		// Split the line by comma.
		const std::vector<std::string> splitLine = split(line, ',');

		const std::string countryName = splitLine[0];
		const std::string continentName = splitLine[3];

		// Get index for country.
		const auto countryIt = std::find(countries.begin(),
			countries.end(),
			countryName);
		const int countryIndex = countryIt - countries.begin();

		// Associate country with continent.
		try {
			continents.at(continentName).push_back(countryIndex);
		}
		// Exception is thrown if continent does not exist.
		catch (...) {
			std::cerr << "Invalid continent detected: " << continentName << " for territory: " << countryName << std::endl;
			return false;
		}

		// Iterate over the remaining strings in splitLine; those respresent
		// the territories adjacent to the current country.
		for (int i = 4; i < splitLine.size(); ++i) {
			const std::string otherCountry = splitLine[i];
			// Get country index.
			const auto otherCountryIt = std::find(countries.begin(),
				countries.end(),
				otherCountry);
			const int otherCountryIndex = countryIt - countries.begin();

			// Check for uniqueness.
			if (otherCountryIndex >= countries.size()) {
				std::cerr << "Duplicate territory detected: " << otherCountry << std::endl;
				return false;
			}

			adjacencyMatrix[countryIndex][otherCountryIndex] = true;
		}
	}

	// Check that the adjacency matrix is valid.
	for (int row = 0; row < adjacencyMatrix.size(); ++row) {
		for (int col = row; row < adjacencyMatrix.size(); ++col) {
			if (adjacencyMatrix[row][col] != adjacencyMatrix[col][row]) {
				std::cerr << "There are territories with adjacent territories that don't match.\n";
				return false;
			}
		}
	}

	return true;
}

