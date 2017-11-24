#include "ContinentControlObserverDecorator.h"

ContinentControlObserverDecorator::ContinentControlObserverDecorator(Observer* decoratedObserver) : ObserverDecorator(decoratedObserver) {}

void ContinentControlObserverDecorator::notifyPhase(int phase) {
	ObserverDecorator::notifyPhase(phase);
}

void ContinentControlObserverDecorator::notifyGame() {
	ObserverDecorator::notifyGame();
}

void ContinentControlObserverDecorator::update() {
	Game* game = getGame();
	Player& player = *game->getCurrentPlayer();
	std::vector<std::string> continents = game->getMap().continentsOwned(player);

	if (!continents.empty()) {
		std::cout << "Continents owned by " << player.getID() << ": ";
		for (const auto& continent : continents) {
			std::cout << continent << ' ';
		}
		std::cout << std::endl;
	}
}