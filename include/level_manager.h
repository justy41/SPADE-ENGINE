#pragma once
#include <iostream>
#include <cmath>
#include <vector>
#include "spade.h"

inline bool lock_1 = false;
inline bool lock_2 = false;
inline bool finished_game = false;
inline int slot_index = 0;

class LevelManager : public Object
{
private:
    
public:
    int level_count;
    bool slot_change;
    
    Sprite* arrow;
    
    LevelManager();
    void create() override;
    void update(float dt) override;
    void draw() override;
};
