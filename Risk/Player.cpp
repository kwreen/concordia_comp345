#include "Player.h"
#include <vector>
#include <iostream>
#include <iomanip>

using std::vector;
using std::cout;
using std::endl;
using std::setw;
using std::setfill;
Player::Player(vector<Country> countries, Hand hand, DiceFacility dice, int playerNumber, Strategy *strategy) : _countries(countries), _hand(hand), _dice(dice), player(playerNumber) {
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

vector<Country>& Player::getCountries() {
    return this->_countries;
}

const vector<Country>& Player::getCountries() const {
    return this->_countries;
}

DiceFacility Player::getDice() const {
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

string Player::getID() {
    return "Player " + to_string(player);
}

int Player::getIDAsInt(){
    return player;
}

void Player::assignCountry(Country c) {
    _countries.push_back(c);
}

void Player::printCountries() {
    for (int i = 0; i<_countries.size(); i++) {
        cout << "Country: " << _countries[i].getName() << " with " << _countries[i].getArmies() << " armies." << endl;
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
    if (phase == 1)
    {
        cout << "[Phase Observer: "<< getID() << " stats]" << endl;
        cout << "Armies: " << getPlayerArmies() << ", Cards: " << getHand().size() << ", Countries Owned: " << getCountries().size() << endl;
        cout << "\nCountries                          Armies" << endl;
        cout << "-------------------------------------------" << endl;
        for (int i = 0; i < _countries.size(); i++)
        {
            cout << left << setw(35) << setfill(' ') << _countries[i].getName() << left << setw(35) << setfill(' ') << _countries[i].getArmies() << endl;
        }
        cout << endl;

    }

    // attack
    else if (phase == 2) {
        cout << "[Phase Observer: "<< getID() << " stats]" << endl;
        cout << "\nCountries                          Armies" << endl;
        cout << "-------------------------------------------" << endl;
        for (int i = 0; i < _countries.size(); i++)
        {
            cout << left << setw(35) << setfill(' ') << _countries[i].getName() << left << setw(35) << setfill(' ') << _countries[i].getArmies() << endl;
        }
        cout << endl;
    }

    // fortification
    else {
        cout << "[Phase Observer: "<< getID() << " stats]" << endl;
        cout << "\nCountries                          Armies" << endl;
        cout << "-------------------------------------------" << endl;
        for (int i = 0; i < _countries.size(); i++)
        {
            cout << left << setw(35) << setfill(' ') << _countries[i].getName() << left << setw(35) << setfill(' ') << _countries[i].getArmies() << endl;
        }
        cout << endl;
    }
}

void Player::notifyGame(int totalCountries,int totalArmies) {
    int currentCountries = _countries.size();
    int currentArmies = getPlayerArmies();
    double percent = (double)currentCountries / totalCountries;
    double percent2 = (double)currentArmies / totalArmies;
    cout << getID() << ": " << currentCountries << "/" << totalCountries << ", " << percent*100 << "% " << "of countries owned, " << currentArmies << "/"
         << totalArmies << ", " << percent2*100 << "% of armies owned "<<
         endl;
}

void Player::setStrategy(Strategy *strategy){
    this->strategy = strategy;
}

Strategy* Player::getStrategy() {
    return this->strategy;
}

