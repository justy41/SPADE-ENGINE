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
    float minSpeed, maxSpeed;
    
    WireManager(float in_between_spawn_time, float minSpeed, float maxSpeed);
    
    void update(float dt) override;
};
