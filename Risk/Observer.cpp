#include "Observer.h"

Observer::~Observer() {};

Game* Observer::getGame() const {
	return game;
}
