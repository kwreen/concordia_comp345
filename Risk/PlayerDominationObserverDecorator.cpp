#include "PlayerDominationObserverDecorator.h"

PlayerDominationObserverDecorator::PlayerDominationObserverDecorator(Observer* decoratedObserver) : ObserverDecorator(decoratedObserver) {}

void PlayerDominationObserverDecorator::notifyPhase(int phase) {
	ObserverDecorator::notifyPhase(phase);
}

void PlayerDominationObserverDecorator::notifyGame() {
	ObserverDecorator::notifyGame();
}

void PlayerDominationObserverDecorator::update() {
	Game* game = getGame();
	Player& player = *game->getCurrentPlayer();
	int playerCountries = player.getCountries().size();
	int totalCountries = game->getMap().getCountries().size();
	double percent = (double) playerCountries / totalCountries;

	std::cout << player.getID() << ": " << playerCountries << "/" << totalCountries << ", " << percent * 100 << "% " << "of countries owned." << std::endl;
}