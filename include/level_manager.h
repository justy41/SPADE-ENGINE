#pragma once
#include <iostream>
#include <cmath>
#include <vector>
#include "spade.h"

class LevelManager : public Object
{
private:
    
public:
    int slot_index;
    int level_count;
    bool slot_change;
    
    Sprite* arrow;
    
    LevelManager();
    void create() override;
    void update(float dt) override;
    void draw() override;
};
