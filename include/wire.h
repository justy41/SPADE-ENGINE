#pragma once
#include <iostream>
#include <cmath>
#include "spade.h"

class Wire : public Sprite
{
private:
    /* data */
public:
    float speed;
    bool big_wire;
    bool upside_down;
    Vector2 limit;
    
    Wire(float x, float y, float speed, bool big_wire, bool upside_down);
    
    void update(float dt) override;
};
