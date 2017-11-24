#pragma once
#include "ObserverDecorator.h"

class ContinentControlObserverDecorator : public ObserverDecorator {
public:
	ContinentControlObserverDecorator(Observer* decoratedObserver);
	void notifyPhase(int phase);
	void notifyGame();
	void update();
};