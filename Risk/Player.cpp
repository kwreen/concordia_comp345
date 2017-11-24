#include "Player.h"
#include <vector>
#include <iostream>

Player::Player(std::vector<Country> countries, Hand hand, DiceFacility dice, int playerNumber, Strategy *strategy) : _countries(countries), _hand(hand), _dice(dice), player(playerNumber) {
        this->setStrategy(strategy);
}

Player::Player(int playerNumber) : player(playerNumber) {}

Hand& Player::getHand() {
    return this->_hand;
}

const Hand& Player::getHand() const {
    return this->_hand;
}

std::vector<Country>& Player::getCountries() {
    return this->_countries;
}

const std::vector<Country>& Player::getCountries() const {
    return this->_countries;
}

DiceFacility Player::getDice() const {
    return this->_dice;
}

void Player::setCountries(std::vector<Country> countries) {
    this->_countries = countries;
}

void Player::setHand(Hand hand) {
    this->_hand = hand;
}

void Player::setDice(DiceFacility dice) {
    this->_dice = dice;
}

std::string Player::getID() {
    return "Player " + std::to_string(player);
}

int Player::getIDAsInt() const {
    return player;
}

void Player::assignCountry(Country c) {
    _countries.push_back(c);
}

void Player::printCountries() {
    for (int i = 0; i<_countries.size(); i++) {
        std::cout << "Country: " << _countries[i].getName() << " with " << _countries[i].getArmies() << " armies." << std::endl;
    }
}

int Player::amtCountries() {
    return _countries.size();
}

int Player::getPlayerArmies() {
    return armies;
}

void Player::initializeArmies(){
    int number = armies;
    int index = 0;
    while (number > 0) {
        if (index>_countries.size() - 1) { index = 0; }
        _countries[index++].increaseArmiesBy(1);
        number--;
    }
}

void Player::setArmies(int nArmies) {
    armies = nArmies;
}

void Player::setStrategy(Strategy *strategy){
    this->strategy = strategy;
}

void Player::executeReinforcement(Player* player){
    this->strategy->reinforcement(player);
}

void Player::executeAttack(Player* player){
    this->strategy->attack(player);
}

void Player::executeFortify(Player* player){
    this->strategy->fortify(player);
}
