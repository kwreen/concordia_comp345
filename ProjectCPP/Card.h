#pragma once

#include "Country.h"
#include <string>

enum CardType { INFANTRY, ARTILLERY, CAVALRY }; //may not work if we need these to be classes with own functions. This is global can be used anywhere as long as included

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
};
