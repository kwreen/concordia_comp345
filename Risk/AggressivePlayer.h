#pragma once
#include "Strategy.h"

class AggressivePlayer : public Strategy {
public:
	AggressivePlayer() = default;
    void reinforcement();
    void attack();
    void fortify();
};
