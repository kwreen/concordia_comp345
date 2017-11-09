#include "Player.h"
#include <vector>
#include <iostream>
#include <iomanip>

Player::Player(std::vector<Country> countries, Hand hand, DiceFacility dice, int playerNumber, Strategy *strategy) : _countries(countries), _hand(hand), _dice(dice), player(playerNumber) {
        this->setStrategy(strategy);
}

//gives them a specific set of countries, Hand, Dice Facility Object
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

int Player::getIDAsInt(){
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
    while (number>0)
    {
        if (index>_countries.size() - 1) { index = 0; }
        _countries[index++].increaseArmies();
        number--;
    }
}

void Player::setArmies(int nArmies) {
    armies = nArmies;
}

void Player::notifyPhase(int phase) {

    // reinforcement
    if (phase == 1) {
        std::cout << "[Phase Observer: "<< getID() << " stats]" << std::endl;
        std::cout << "Armies: " << getPlayerArmies() << ", Cards: " << getHand().size() << ", Countries Owned: " << getCountries().size() << std::endl;
        std::cout << "\nCountries                          Armies" << std::endl;
        std::cout << "-------------------------------------------" << std::endl;
        for (int i = 0; i < _countries.size(); i++) {
            std::cout << std::left << std::setw(35) << std::setfill(' ') << _countries[i].getName() << std::left << std::setw(35) << std::setfill(' ') << _countries[i].getArmies() << std::endl;
        }
        std::cout << std::endl;
    }

    // attack
    else if (phase == 2) {
        std::cout << "[Phase Observer: "<< getID() << " stats]" << std::endl;
        std::cout << "\nCountries                          Armies" << std::endl;
        std::cout << "-------------------------------------------" << std::endl;
        for (int i = 0; i < _countries.size(); i++) {
            std::cout << std::left << std::setw(35) << std::setfill(' ') << _countries[i].getName() << std::left << std::setw(35) << std::setfill(' ') << _countries[i].getArmies() << std::endl;
        }
        std::cout << std::endl;
    }

    // fortification
    else {
        std::cout << "[Phase Observer: "<< getID() << " stats]" << std::endl;
        std::cout << "\nCountries                          Armies" << std::endl;
        std::cout << "-------------------------------------------" << std::endl;
        for (int i = 0; i < _countries.size(); i++) {
            std::cout << std::left << std::setw(35) << std::setfill(' ') << _countries[i].getName() << std::left << std::setw(35) << std::setfill(' ') << _countries[i].getArmies() << std::endl;
        }
        std::cout << std::endl;
    }
}

void Player::notifyGame(int totalCountries) {
    int currentCountries = _countries.size();
    double percent = (double)currentCountries / totalCountries;
	std::cout << getID() << ": " << currentCountries << "/" << totalCountries << ", " << percent * 100 << "% " << "of countries owned." << std::endl;
}

void Player::setStrategy(Strategy *strategy){
    this->strategy = strategy;
}

Strategy* Player::getStrategy() {
    return this->strategy;
}
