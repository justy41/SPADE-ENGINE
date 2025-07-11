#pragma once
#include <iostream>
#include <cmath>
#include <vector>
#include <memory>
#include "spade.h"
#include "wire.h"

class WireManager : public Object
{
private:
    /* data */
public:
    std::vector<std::unique_ptr<Wire>> wires;
    float spawn_timer;
    float spawn_timer_value;
    
    WireManager(float in_between_spawn_time);
    
    void update(float dt) override;
};
