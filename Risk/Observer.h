#pragma once
class Observer
{
public:
	Observer() {};
	~Observer() {};
	virtual void showStats() = 0;
};

