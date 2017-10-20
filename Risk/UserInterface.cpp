#include "UserInterface.h"
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
	std::cout << "Please select a map to use.\n";
	int mapChoice;

	for (int i = 2; i < files.size(); ++i) {
		std::cout << i - 1 << ". " << removeExtension(files[i]) << std::endl;
	}

	std::cout << ">>> ";
	std::cin >> mapChoice;
	while (mapChoice < 1 || mapChoice >= files.size() - 1) {
		std::cerr << "Invalid choice. Try again.\n";
		std::cout << ">>> ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> mapChoice;
	}
	return "Resources/" + files[mapChoice + 1];
}

int UserInterface::selectNumPlayers() {
	std::cout << "\n";

	std::cout << "Select the number of players (2-6):\n";
	int nPlayers;
	
	std::cout << ">>> ";
	std::cin >> nPlayers;
	while (nPlayers < 2 || nPlayers > 6) {
		std::cerr << "Invalid choice. Try again.\n";
		std::cout << ">>> ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> nPlayers;
	}

	return nPlayers;
}