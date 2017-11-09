#include "Player.h"
#include <vector>
#include <iostream>
#include <iomanip> //for nice output

using std::vector;
using std::cout;
using std::endl;
using std::setw;
using std::setfill;
Player::Player(vector<Country> countries, Hand hand, DiceFacility dice, int playerNumber, Strategy *strategy) : _countries(countries), _hand(hand), _dice(dice), player(playerNumber) {
        this->setStrategy(strategy);

} //gives them a specific set of countries, Hand, Dice Facility Object
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

string Player::getID()
{
    return "Player " + to_string(player);
}

int Player::getIDAsInt() //gets id as strictly an int
{
    return player;
}

void Player::assignCountry(Country c) //assigns a country to the player. See startup() in mainGameLoop
{
    _countries.push_back(c); //<-- size is correct here,seems to be inserting, fine, completetly deleted in countries() method below and when returning it: getCountries
}

void Player::printCountries() //prints countries player currently owns
{
    for (int i = 0; i<_countries.size(); i++)
    {
        cout << "Country: " << _countries[i].getName() << " with " << _countries[i].getArmies() << " armies." << endl;
    }
}

int Player::amtCountries() //returns how many countries player has
{
    return _countries.size();
}

void Player::increasePlayerArmies()
{
    ++armies;
}

int Player::getPlayerArmies() //will need to add armies gotten from exchange() in players hand here
{
    return armies;
}

void Player::initializeArmies() //used strictly in main game loop class for initalization step
{
    int number = armies;
    int index = 0;
    while (number>0)
    {
        if (index>_countries.size() - 1) { index = 0; }
        _countries[index++].increaseArmies();
        number--;
    }
}

void Player::setArmies(int nArmies)
{
    armies = nArmies;
}


void Player::showStats() {
    cout << getID() << " has: " << endl;
    cout << getPlayerArmies() << " armies." << endl;
    cout << "Countries                          Armies" << endl;
    cout << "-------------------------------------------" << endl;
    for (int i = 0; i < _countries.size(); i++) {
        cout << left << setw(35) << setfill(' ') << _countries[i].getName() << left << setw(35) << setfill(' ') << _countries[i].getArmies() << endl;
    }
}

void Player::update() {
	showStats();
}

void Player::setStrategy(Strategy *strategy){
    this->strategy = strategy;
}

Strategy* Player::getStrategy() {
    return this->strategy;
}