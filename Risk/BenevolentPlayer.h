#pragma once
#include "Strategy.h"

class BenevolentPlayer : public Strategy {
private:

public:
    void reinforcement();
    void attack();
    void fortify();
};
