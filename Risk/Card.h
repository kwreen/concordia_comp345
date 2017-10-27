#pragma once

#include "Country.h"
#include <iostream>
#include <string>

enum CardType {
	INFANTRY, ARTILLERY, CAVALRY
};

class Card {
private:
	Country country;
	CardType cardType;

public:
	Card(const Country& country, CardType cardType) :
			country(country), cardType(cardType) {}

	Country getCountry() const;

	void setCountry(const Country& country);

	CardType getCardType() const;

	std::string getCardTypeAsString() const;

	void setCardType(CardType cardType);

	friend std::ostream& operator<<(std::ostream& os, const Card& card) {
		os << "country: " << card.country.getName() << ", type: ";
		switch (card.cardType) {
			case INFANTRY:
				os << "infantry";
				break;
			case ARTILLERY:
				os << "artillerty";
				break;
			case CAVALRY:
				os << "cavalry";
				break;
		}
		return os;
	}
};
