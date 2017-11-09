#pragma once
#include "Strategy.h"

class AggressivePlayer : public Strategy {
private:

public:
    void reinforcement();
    void attack();
    void fortify();

};
