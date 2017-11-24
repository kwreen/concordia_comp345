#pragma once
#include "ObserverDecorator.h"

class PlayerDominationObserverDecorator : public ObserverDecorator {
public:
	PlayerDominationObserverDecorator(Observer* decoratedObserver);
	void notifyPhase(int phase);
	void notifyGame();
	void update();
};
