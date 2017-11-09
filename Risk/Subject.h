#pragma once
#include "Player.h"
#include <vector>
#include <list>

class Observer;

class Subject {
private:
	std::list<Observer*> *_observers;

protected:
	Subject() {};

public:
	virtual ~Subject() {};
	virtual void attach(Observer *);
	virtual void detach(Observer *);
	virtual void notify();
};