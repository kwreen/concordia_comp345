#include "Country.h"

std::string Country::getName() const {
	return name;
}

void Country::setName(const std::string& name) {
	this->name = name;
}

bool Country::operator==(const Country& other) const {
	return name == other.name;
}

bool Country::operator<(const Country& second) const {
	return name < second.name;
}
