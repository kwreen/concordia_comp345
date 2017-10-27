#pragma once

#include <string>

class Country {
private:
	std::string name;
	int armies;

public:
	Country() = default;

	Country(std::string name) : name(name), armies(0) {}

	std::string getName() const;

	void setName(const std::string& name);

	bool operator==(const Country& other) const;

	bool operator<(const Country& second) const;

	void increaseArmies(); // TODO: Rename to incrementArmies

	int getArmies() const;

	void setArmies(int n); //sets amount of armies on country

	void increaseArmiesBy(int n);

	void decreaseArmiesBy(int n);

	bool operator==(const Country& other) {
		return name == other.name;
	}
};
