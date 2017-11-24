#include "ObserverDecorator.h"

ObserverDecorator::ObserverDecorator(Observer* decoratedObserver) {
	this->decoratedObserver = decoratedObserver;
}

void ObserverDecorator::notifyPhase(int phase) {
	this->decoratedObserver->notifyPhase(phase);
}

void ObserverDecorator::notifyGame() {
	this->decoratedObserver->notifyGame();
}