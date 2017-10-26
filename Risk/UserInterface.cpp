#include "UserInterface.h"
#include "Map.h"
#include "MapLoader.h"
#include <iostream>
#include <limits>
#include <string>
#include <vector>

#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#else
#include <sys/types.h>
#include <dirent.h>
#endif


std::vector<std::string> listFiles(const std::string& directory) {
#ifdef _WIN32
	// windows implementation
	std::vector<std::string> files;
	std::string pattern(directory);
	pattern.append("\\*");
	WIN32_FIND_DATA data;
	HANDLE hFind;
	if ((hFind = FindFirstFile(pattern.c_str(), &data)) != INVALID_HANDLE_VALUE) {
		do {
			files.push_back(data.cFileName);
		} while (FindNextFile(hFind, &data) != 0);
		FindClose(hFind);
	}

	return files;
#else
	// Linux + Mac implementation
	std::vector<std::string> files;
	DIR* dirp = opendir(directory.c_str());
	struct dirent * dp;
	while ((dp = readdir(dirp)) != NULL) {
		files.push_back(dp->d_name);
	}
	closedir(dirp);
	return files;
#endif
}

std::string removeExtension(const std::string& file) {
	int i;
	for (i = 0; i < file.size(); ++i) {
		if (file[i] == '.') break;
	}

	return file.substr(0, i);
}


std::string UserInterface::selectMap() {
	const auto files = listFiles("Resources");
	bool validMap = false;
	int mapChoice;
	std::string mapName;

	std::cout << "Please select a map to use.\n";

	for (int i = 2; i < files.size(); ++i) {
		std::cout << i - 1 << ". " << removeExtension(files[i]) << std::endl;
	}
	
	do { 
		std::cout << std::endl;
		std::cout << ">>> ";
		std::cin >> mapChoice;
		while (mapChoice < 1 || mapChoice >= files.size() - 1) {
			std::cerr << "Invalid choice. Try again.\n" << std::endl;
			std::cout << ">>> ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin >> mapChoice;
		}

		mapName = "Resources/" + files[mapChoice + 1];

		Map map = MapLoader::loadMap(mapName);

		if (map.getCountries().size() == 0) {
			std::cout << "Invalid map file. Choose again." << std::endl;
			validMap = false;
		}
		else {
			validMap = true;
		}
	} while (!validMap);

	return mapName;
}

int UserInterface::selectNumPlayers() {
	std::cout << "\n";

	std::cout << "Select the number of players (2-6):\n";
	int nPlayers;
	
	std::cout << ">>> ";
	std::cin >> nPlayers;
	while (nPlayers < 2 || nPlayers > 6) {
		std::cerr << "Invalid choice. Try again.\n" << std::endl;
		std::cout << ">>> ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> nPlayers;
	}

	return nPlayers;
}

Country& UserInterface::selectCountry(Player& player, Map map) {
	std::vector<Country>& countries = player.getCountries();
	int sourceChoice;

	std::cout << "Available source countries:" << std::endl;
	for (int i = 0; i < countries.size(); i++) {
		std::cout << i + 1 << ". " << countries[i].getName() << std::endl;
	}

	std::cout << std::endl;
	std::cout << ">>> ";
	std::cin >> sourceChoice;

	while ((sourceChoice < 1) || (sourceChoice > countries.size())) {
		std::cerr << "Invalid choice. Try again.\n" << std::endl;
		std::cout << ">>> ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> sourceChoice;
	}

	return countries[sourceChoice - 1];
}

Country& UserInterface::selectAdjacentCountry(Country& country, Map map) {
	// TODO: Player has to own adjacent countries too
    std::cout << "Available target/adjacent countries:" << std::endl;
	std::vector<Country> adjacentCountries = map.adjacent(country);
	int targetChoice;

	for (int i = 0; i < adjacentCountries.size(); i++) {
		std::cout << i + 1 << ". " << adjacentCountries[i].getName() << std::endl;
	}

	std::cout << std::endl;
	std::cout << ">>> ";
	std::cin >> targetChoice;

	while ((targetChoice < 1) || (targetChoice > adjacentCountries.size())) {
		std::cerr << "Invalid choice. Try again.\n" << std::endl;
		std::cout << ">>> ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> targetChoice;
	}

	return adjacentCountries[targetChoice - 1];
}

int UserInterface::selectArmiesToFortify(Country& source) {
	int nArmies;

	std::cout << source.getName() << " has " << source.getArmies() << " armies." << std::endl;
	std::cout << "Enter the number of armies you want to move to your target country." << std::endl;
	
	std::cout << ">>> ";
	std::cin >> nArmies;

	while ((nArmies < 1) || (nArmies > source.getArmies() - 1)) {
		std::cerr << "Invalid choice. Try again.\n" << std::endl;
		std::cout << ">>> ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> nArmies;
	}

	return nArmies;
}

