#include "Map.h"
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

int main3() {
	Map map;
	bool loadMapSuccess = map.loadMap("World.map");
	if (!loadMapSuccess) {
		std::cerr << "Exiting\n";
		return -1;
	}
	//map.print();
	bfs(map);
	system("pause");
}