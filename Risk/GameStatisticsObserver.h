#pragma once
#include "Observer.h"
#include "Game.h"

class GameStatisticsObserver : public Observer {
private:
	int previousTurn = 0;

public:
	GameStatisticsObserver(Game* game) : Observer(game) {}
	void notifyPhase(int phase);
	void notifyGame();
	void update();
};