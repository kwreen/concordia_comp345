#pragma once
#include "Player.h"

class Observer {

public:
    Observer();
	~Observer();
	virtual void notifyPhase(int phase) = 0;
    virtual void notifyGame() = 0;
};
