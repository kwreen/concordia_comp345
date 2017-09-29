#pragma once

#include "Country.h"
#include <string>

enum CardType { INFANTRY, ARTILLERY, CAVALRY };

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
