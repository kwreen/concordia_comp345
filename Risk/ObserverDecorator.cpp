#include "ObserverDecorator.h"

ObserverDecorator::ObserverDecorator(Observer* decoratedObserver) : Observer(decoratedObserver->getGame()) {
	this->decoratedObserver = decoratedObserver;
}	

void ObserverDecorator::notifyPhase(int phase) {
	this->decoratedObserver->notifyPhase(phase);
}

void ObserverDecorator::notifyGame() {
	this->decoratedObserver->notifyGame();
}

void ObserverDecorator::update() {
	this->decoratedObserver->update();
}