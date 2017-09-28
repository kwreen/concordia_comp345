#pragma once

#include <string>

class Country {
	private:
		std::string name;

	public:
		Country(std::string name) : name(name) {}

		std::string getName() const;

		void setName(const std::string& name);

		bool operator==(const Country& other) const;
};
