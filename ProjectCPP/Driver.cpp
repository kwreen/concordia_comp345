/*
 * Driver.cpp
 *
 *  Created on: Oct 7, 2017
 *      Author: Jordan
 */


#include "Deck.h"
#include "Hand.h"
#include "Player.h"
#include "Card.h" //just incase want to grab cards
#include "Country.h"
#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;
class MainGameLoop
{
	int seed;
	vector<Player> turns;
	vector<Country>countries; //will grab countries from map(this needs to be added to replace assignCountries
	vector<Player> startGame(int players) //creates an ordered vector of players and returns it. This is used only by assignTurns() and the class thus is private
	{
		vector<Player> p;
		if(players<2 || players > 6)
		{
			cout<<"Invalid Number of players,exiting program"; //make sure to create a viable vector of players
			exit(0);
		}
		if(players == 2)
		{
			Player p1(1); //Created a new player constructor just to accept a playerid, if more is needed use another constructor
			Player p2(2);
			p.push_back(p1);
			p.push_back(p2);
		}
		else if(players == 3)
		{
			Player p1(1);
			Player p2(2);
			Player p3(3);
			p.push_back(p1);
			p.push_back(p2);
			p.push_back(p3);
		}
		else if(players == 4)
		{
			Player p1(1);
			Player p2(2);
			Player p3(3);
			Player p4(4);
		    p.push_back(p1);
		    p.push_back(p2);
			p.push_back(p3);
			p.push_back(p4);
		}
		else if(players == 5)
		{
			Player p1(1);
			Player p2(2);
			Player p3(3);
			Player p4(4);
			Player p5(5);
			p.push_back(p1);
		    p.push_back(p2);
		    p.push_back(p3);
		    p.push_back(p4);
		    p.push_back(p5);
		}
		else
		{
			Player p1(1);
			Player p2(2);
			Player p3(3);
			Player p4(4);
			Player p5(5);
			Player p6(6);
			p.push_back(p1);
			p.push_back(p2);
		    p.push_back(p3);
		    p.push_back(p4);
			p.push_back(p5);
			p.push_back(p6);
		}
		return p;

	}
public:
	MainGameLoop()
	{
	 int random = rand() %100; //place seed for generator
	 srand(random);
	}
	void assignTurns(int players) // can only be 2-6 player. Accepts an array of players and gives them randomturns
	{
		vector<Player> p = startGame(players);
		int numPlayers = p.size();
		int loop = numPlayers;
		for(int i=0;i<loop;i++)
		{
			int r = rand() % numPlayers;
			turns.push_back(p.at(r));
			p.erase(p.begin() + r); //erase player from player array
			numPlayers = p.size();


		}

	}
	vector<Player> getTurns() //returns vector pointer of player turns
	{
		return turns;
	}
	int nPlayers() //returns the amount of players for this game. Note assignTurns needs to be called first
	{
		return turns.size();
	}
	void setCountries() //will not be needed just use it for testing purposes(grab from map later).
	{
		Country c1("Canada");
		Country c2("United States");
		Country c3("Mexico");
		Country c4("Venezuala");
		Country c5("England");
		Country c6("Germany");
		Country c7("Russia");
		Country c8("Italy");
		Country c9("Greece");
		Country c10("China");
		countries.push_back(c1); //<-- all is inserted properly i checked
		countries.push_back(c2);
		countries.push_back(c3);
		countries.push_back(c4);
		countries.push_back(c5);
		countries.push_back(c6);
		countries.push_back(c7);
		countries.push_back(c8);
		countries.push_back(c9);
		countries.push_back(c10);

	}
	void assignArmies() //again make sure assignTurns is called first
	{
		int number; //decides initial number of armies to put on players countries

		if(turns.size() == 2)
		{
			number = 40;
		}
		else if(turns.size() == 3)
		{
			number = 35;
		}
		else if(turns.size() == 4)
		{
			number = 30;
		}
		else if(turns.size() == 5)
		{
			number=25;
		}
		else if(turns.size() == 6)
		{
			number = 20;
		}
		else
		{
			cout<<"Incorrect number of players";
			return;
		}
		int i = 0;
		while(number>0) //assign total initial armies to players
		{
			if(i>turns.size()-1) { i=0;} //wrap around array/round robin logic
			turns[i++].increasePlayerArmies();
			number--;

		}
		for(int i=0;i<turns.size();i++) //assign total armies to player countries
		{
			turns[i].countryArmies();
		}




	}
	void startUp() //does bulk of part 2. Also again assigntTurns() must be called before this
	{
     setCountries(); //as stated this will not be needed,test purposes
     int index = 0;
     for(int i=0;i<countries.size();i++) //size does =  10
     {
    	 if(index == nPlayers()) index=0; //if index gets after last player,wrap around turns array to start again at player1
    	turns[index++].assignCountry(countries[i]); //<--this not insserting at all

     }
     assignArmies(); //assign armies to these countries

	}

    void playGame(int players) //main game loop(part3,4,5,6)
    {

    	/*
    	 *Pseudocode
    	    while(owned == false)
    	    {
    	       for(int i=0;i<turns.size();i++)
    	       {
    	        if(turns[i].countrySize() == totalNumberofCountries)
    	        {
    	         cout<<turns[i].playerAsString() << " wins! ";
    	         owned = true;
    	         break;
    	        }
    	       turns[i].reinforce();
    	       turns[i].attack();
    	       turns[i]. fortify();
    	    }

    	}

      */
    }
};
int main()
{

 cout<<"Player turns for Game:" <<endl;
 MainGameLoop l;
 l.assignTurns(4); //This method will assign turns to each player in the game.This example 4 players.
 vector<Player> p = l.getTurns(); //returns turn vector
 for(int i=0;i<p.size();i++)
 {
	 cout<<"Turn " << i+1<<":" << p[i].playerAsString()<<endl;
 }
 //assigning countries
 l.startUp();  //give each player a country in round robin fashion and assign armies to each of those countries
 //get updated array with assigned countries
 p=l.getTurns();
 p[0].countries();
 p[1].countries();
 p[2].countries();
 p[3].countries();

 //get player armies on countries
 vector<Country> playera = p[0].getCountries();
 vector<Country> playerb = p[1].getCountries();
 vector<Country> playerc = p[2].getCountries();
 vector<Country> playerd = p[3].getCountries();
 //get # of initial armies put on this country
 cout<<"# of armies on" << playera[0].getName() << ": " << playera[0].getArmies()<<endl;
 //get total amount of armies distributed to make sure it works(This is same as just grabbing armies from player class but making sure distribution is correct)
 int armiesA=0;
 int armiesB = 0;
 int armiesC = 0;
 int armiesD = 0;
 for(int i=0;i<playera.size();i++)
 {
	 armiesA+=playera[i].getArmies();
 }
 for(int i=0;i<playerb.size();i++)
 {
	 armiesB+=playerb[i].getArmies();
 }
 for(int i=0;i<playerc.size();i++)
 {
	 armiesC+=playerc[i].getArmies();
 }
 for(int i=0;i<playerd.size();i++)
 {
	 armiesD+=playerd[i].getArmies();
 }
 cout<<"Total amount of armies distributed: " << armiesA + armiesB + armiesC + armiesD <<endl; //<-- this is correct distribution
  return 0;
}

