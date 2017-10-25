#pragma once

#include <string>

class Country {
private:
	std::string name;
	int armies = 0;

public:
	Country() = default;

	Country(std::string name) : name(name) {}

	std::string getName() const;

	void setName(const std::string& name);

	bool operator==(const Country& other) const;

	bool operator<(const Country& second) const;

	void increaseArmies(); //increases army count on this country

	int getArmies();

	void setArmies(int n); //sets amount of armies on country

};
