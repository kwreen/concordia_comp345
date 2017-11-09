#pragma once
#include "Strategy.h"

class HumanPlayer : public Strategy {
private:

public:
    HumanPlayer() = default;
    void reinforcement();
    void attack();
    void fortify();

};