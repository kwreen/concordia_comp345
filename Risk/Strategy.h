#pragma once

class Strategy {

public:
    virtual void reinforcement(){};
    virtual void attack(){};
    virtual void fortify(){};
    virtual ~Strategy(){};
};