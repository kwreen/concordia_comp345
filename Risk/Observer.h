#pragma once
#include "Player.h"
#include "Game.h"

class Observer {
private:
	Game* game;
public:
	Observer(Game* game) : game(game) {}
	~Observer();
	virtual void notifyPhase(int phase) = 0;
    virtual void notifyGame() = 0;
	virtual void update() = 0;
	Game* getGame() const;
};
