#include "Player.h";
#include <vector>;
#include <iostream>;

using std::vector;
using std::cout;
using std::endl;

Player::Player(vector<Country> countries, Hand hand, DiceFacility dice) {
	this->_countries = countries;
	this->_hand = hand;
	this->_dice = dice;
}

inline vector<Country>& Player::getCountries() const {
	return (vector<Country>&)this->_countries;
}

inline Hand Player::getHand() const {
	return this->_hand;
}

inline DiceFacility Player::getDice() const {
	return this->_dice;
}

void Player::setCountries(vector<Country> countries) {
	this->_countries = countries;
}

void Player::setHand(Hand hand) {
	this->_hand = hand;
}

void Player::setDice(DiceFacility dice) {
	this->_dice = dice;
}

void Player::reinforce() {
	// TODO: Implement reinforce mechanism
	cout << "Player " << this << " has reinforced." << endl;
}

void Player::attack() {
	// TODO: Implement attack mechanism
	cout << "Player " << this << " has attacked." << endl;
}

void Player::fortify() {
	// TODO: Implement fortify mechanism
	cout << "Player " << this << " has fortified." << endl;
}
