#pragma once
#include "Observer.h"
#include "Game.h"

class GameStatisticsObserver : public Observer {
private:
	Game* game;

public:
	GameStatisticsObserver(Game* game) : game(game) {}
	void notifyPhase(int phase);
	void notifyGame();
};