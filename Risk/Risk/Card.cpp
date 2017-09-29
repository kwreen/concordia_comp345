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

std::string Card::getCardTypeAsString() const {
	if (cardType == INFANTRY) return "infantry";
	if (cardType == ARTILLERY) return "artillery";
	if (cardType == CAVALRY) return "cavalry";
}

void Card::setCardType(CardType cardType) {
	this->cardType = cardType;
}
