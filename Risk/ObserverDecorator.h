#pragma once
#include "Observer.h"

class ObserverDecorator : public Observer {
protected:
	Observer* decoratedObserver;

public:
	ObserverDecorator(Observer *decoratedObserver);
	void notifyPhase(int phase);
	void notifyGame();
};