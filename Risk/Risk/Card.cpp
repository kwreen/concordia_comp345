#include "Card.h"

Country Card::getCountry() const {
	return country;
}

void Card::setCountry(const Country& country) {
	this->country = country;
}

CardType Card::getCardType() const {
	return cardType;
}

void Card::setCardType(CardType cardType) {
	this->cardType = cardType;
}
