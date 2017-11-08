#pragma once
#include "Player.h"
#include <vector>
using namespace std;
class Subject
{
	vector<Player> *observers; //pointer to player array which will consitute observers. Do not need polymorphism here as all same objects players, no pointers needed.

public:
	//~Subject();
	void attatch(vector<Player>& p); //uses player vector as an observer vector
	void notify();
};