/*
 * Dice.cpp
 *
 *  Created on: Sep 21, 2017
 *      Author: Jordan
 */
#include <iostream>
#include <stdlib.h> //c file for random number generator
using namespace std;
class Dice
{
private:
	int* p; //this will point to previous turn rolls, with either 1,2 or 3 die.If there are 1 die then only 1 space for turn if 2 2 if 3 3
	void rezize();//used to make array dynamic,like a vector/arraylist
	int listS;//how many elements up to now
	int arrayS;//capacity of array
	int n; //returns number of die for this object
	int seed;//seed value for random # generator

public:
	 Dice(int);//grabs number of dice to be used
	 void roll();
	 int* previousTurns(); //returns a pointer to the previousTurns array (*p)
	 int listSize(); //returns listS
	 int arraySize();//returns arrayS
};
Dice::Dice(int numberofdie)
{
	n = numberofdie;
	p = new int[50]; //initial size of array will be 50
	listS=0;
	arrayS = 50;
	seed = rand() %100;
	srand(seed);


}
int Dice::arraySize()
{
	return arrayS;
}
int Dice::listSize()
{
	return listS;
}
void Dice::rezize()
{
	int* b = new int[arrayS * 2];
	for(int i=0;i<arrayS;i++)
	{
		p[i] = b[i];
	}
	p = b;
}
void Dice::roll()
{
	cout<<"Rolling Dice..\n";
	if(n==1) //1 dice
	{
		int roll =rand() %6 + 1;
		cout<<"You rolled a:" <<roll<<"\n";
		p[listS++] = roll;
	}
	else if(n==2)//2 die
	{
		int roll1 = rand()%6 + 1;
		int roll2 = rand()%6+1;
		cout<<"You rolled a "<< roll1 <<" and a" << roll2<<"\n";
		p[listS++] = roll1;
		p[listS++] = roll2;
	}
	else //3 die
	{
		int roll1 = rand()%6 + 1;
		int roll2 = rand()%6 + 1;
		int roll3 = rand()%6 +1;
		cout<<"You rolled a :" <<roll1<<" , a " <<roll2 << " and a" <<roll3<<"\n";
		p[listS++] = roll1;
		p[listS++] = roll2;
		p[listS++] = roll3;
	}

}
int* Dice::previousTurns() //returns pointer to previous turn array
{
	return p;
}

int main()
{
	Dice dice1(1);
	dice1.roll();
	dice1.roll();
	dice1.roll();
	Dice dice2(2);
	dice2.roll();
	dice2.roll();
	dice2.roll();
	int* s = dice2.previousTurns();

	for(int i=0;i<dice2.listSize();i++)
	{
		cout<<s[i]<< ',' ;
	}
	return 0;
}



