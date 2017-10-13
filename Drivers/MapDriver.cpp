#include "Risk/Map.h"
#include "Risk/MapLoader.h"
#include <iostream>
#include <queue>
#include <set>

void bfs(const Map& map) {
	std::queue<Country> toVisit;
	std::set<Country> visited;
	toVisit.push(map.getCountries()[0]);

	while (!toVisit.empty()) {
		Country next = toVisit.front();
		toVisit.pop();
		
		// Skip if node visited.
		if (visited.find(next) != visited.end()) {
			continue;
		}

		std::cout << next.getName() << std::endl;
		visited.insert(next);

		std::vector<Country> adjacentNodes = map.adjacent(next);
		for (const Country& country : adjacentNodes) {
			toVisit.push(country);
		}
	}
}

void bfs_continent(const Map& map, const std::string& continent) {
	std::queue<Country> toVisit;
	std::set<Country> visited;
	toVisit.push(map.getContinent(continent)[0]);

	while (!toVisit.empty()) {
		Country next = toVisit.front();
		toVisit.pop();

		// Skip if node visited.
		if (visited.find(next) != visited.end()) {
			continue;
		}

		std::cout << next.getName() << std::endl;
		visited.insert(next);

		std::vector<Country> adjacentNodes = map.adjacentInContinent(next, continent);
		for (const Country& country : adjacentNodes) {
			toVisit.push(country);
		}
	}
}

int main() {
	Map map = MapLoader::loadMap("World.map");
	if (map.getCountries().size() == 0) {
		std::cerr << "Exiting\n";
		return -1;
	}
	map.print();

	std::cout << std::endl;

	bfs(map);

	std::cout << std::endl;

	for (const auto& continent : map.getContinentNames()) {
		std::cout << "Traversal for " << continent << ": " << std::endl;
		bfs_continent(map, continent);
		std::cout << std::endl;
	}

	system("pause");
}