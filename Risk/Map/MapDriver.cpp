#include "Map.h"
#include <iostream>

using std::cout;
using std::endl;

int main()
{
	Map map;
	Country a("Canada", "North America");
	cout << a.getContinent() << endl;
	Country b("USA");
	Country c("test");
	map.addCountry("Canada");
	map.addCountry("USA");
	map.addCountry("test");
	//cout << map.getIndex("United States") << endl;
	map.addAdjacent(a, b);
	map.addAdjacent(a, c);
	map.showAdjacent(a);
	cout << map.getSize() << endl;
	map.getCountries();

	return 0;
}