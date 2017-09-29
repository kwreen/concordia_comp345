#include "MapLoader.h"
#include "Map.h"
#include <iostream>
#include <sstream>
#include <fstream>

std::vector<std::string> split(const std::string& input, char delim) {
	std::stringstream ss(input);
	std::string segment;
	std::vector<std::string> contents;
	while (std::getline(ss, segment, delim)) {
		contents.push_back(segment);
	}
	return contents;
}

Map MapLoader::loadMap(std::string filename) {
	Map map;

	std::ifstream ifs(filename);
	std::string line;

	// Get the continents.
	while (std::getline(ifs, line) && line != "[Continents]") {}
	while (std::getline(ifs, line) && line != "") {
		const int equalsIndex = line.find('=');
		const std::string continent = line.substr(0, equalsIndex);
		map.continents.insert({ continent, std::vector<int>() });
	}

	// Get all the territories.
	while (std::getline(ifs, line) && line != "[Territories]") {}
	while (std::getline(ifs, line)) {
		// Get the territory name.
		if (line != "") {
			const int commaIndex = line.find(',');
			const std::string countryName = line.substr(0, commaIndex);
			// Confirm that country is unique.
			if (std::find(map.countries.begin(), map.countries.end(), countryName) != map.countries.end()) {
				std::cerr << "Duplicate territory detected: " << countryName << std::endl;
				return Map();
			}
			map.countries.push_back(countryName);
		}
	}

	// Re-read file.
	ifs.clear();
	ifs.seekg(0, ifs.beg);

	// Initialize the adjacency matrix.
	map.adjacencyMatrix.resize(map.countries.size(), std::vector<bool>(map.countries.size()));

	// Set adjacencyMatrix and continents territory by territory.
	while (std::getline(ifs, line) && line != "[Territories]") {}
	while (std::getline(ifs, line)) {
		if (line == "") {
			continue;
		}

		// Split the line by comma.
		const std::vector<std::string> splitLine = split(line, ',');

		const std::string countryName = splitLine[0];
		const std::string continentName = splitLine[3];

		// Get index for country.
		const auto countryIt = std::find(map.countries.begin(),
			map.countries.end(),
			countryName);
		const int countryIndex = countryIt - map.countries.begin();

		// Associate country with continent.
		try {
			map.continents.at(continentName).push_back(countryIndex);
		}
		// Exception is thrown if continent does not exist.
		catch (...) {
			std::cerr << "Invalid continent detected: " << continentName << " for territory: " << countryName << std::endl;
			return Map();
		}

		// Iterate over the remaining strings in splitLine; those respresent
		// the territories adjacent to the current country.
		for (int i = 4; i < splitLine.size(); ++i) {
			const std::string otherCountry = splitLine[i];
			// Get country index.
			const auto otherCountryIt = std::find(map.countries.begin(),
				map.countries.end(),
				otherCountry);
			const int otherCountryIndex = otherCountryIt - map.countries.begin();

			// Check for uniqueness.
			if (otherCountryIndex >= map.countries.size()) {
				std::cerr << "Duplicate territory detected: " << otherCountry << std::endl;
				return Map();
			}

			map.adjacencyMatrix[countryIndex][otherCountryIndex] = true;
		}
	}

	// Check that the adjacency matrix is valid.
	for (int row = 0; row < map.adjacencyMatrix.size(); ++row) {
		for (int col = row; col < map.adjacencyMatrix.size(); ++col) {
			if (map.adjacencyMatrix[row][col] != map.adjacencyMatrix[col][row]) {
				std::cerr << "There are territories with adjacent territories that don't match.\n";
				return Map();
			}
		}
	}

	return map;
}