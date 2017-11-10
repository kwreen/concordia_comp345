#pragma once
#include "Strategy.h"

class BenevolentPlayer : public Strategy {
private:

public:
    void reinforcement(Player* player);
    void attack();
    void fortify(Player* player);
};
