#pragma once

class Observer {
protected:
	Observer();

public:
	~Observer();
	virtual void update() = 0;
};
