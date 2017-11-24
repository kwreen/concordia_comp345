#pragma once
#include <list>

class Observer;

class Subject {
private:
	std::list<Observer*> *_observers;
    int phase;
    int totalCountries;

protected:
	Subject();

public:
	virtual ~Subject();
	virtual void attach(Observer *);
	virtual void detach(Observer *);
	virtual void notifyPhaseAll();
    virtual void notifyGameAll();
	virtual void notify();
    virtual void setPhase(int& phase);
};