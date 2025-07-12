#pragma once
#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include "spade.h"
#include "player.h"

class ScoreManager : public Object {
private:

public:
    int score;
    int prev_score;
    int dif_score;
    Player* player;
    
    ScoreManager(Player* player);
    void update(float dt) override;
    void draw() override;
    void reset_score();
};