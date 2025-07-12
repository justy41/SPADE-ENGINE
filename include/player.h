#pragma once
#include <iostream>
#include <cmath>
#include "spade.h"

class Player : public Sprite
{
private:
    /* data */
public:
    float acc, jumpForce, gravityForce, fallMultiplier;
    bool touched_right;
    bool can_touch_right;
    bool touched_left;
    bool can_touch_left;
    bool immune;
    bool hit;
    float immunity_timer;
    float immunity_timer_value;
    
    Player(float x, float y, float acc, float jumpForce, float gravityForce = 640, float fallMultiplier = 1.5f);
    
    void update(float dt) override;
    void draw() override;
    void on_collision(Base* other) override;
    void SetPlayerBounds();
    void RotatePlayer(float degrees_per_frame, float dt);
    void SetGravity(float g);
    
    ~Player() {}
};