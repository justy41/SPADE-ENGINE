#include "wire.h"

Wire::Wire(float x, float y, float speed, bool big_wire, bool upside_down) : Sprite(x, y) {
    if(x > GAME_WIDTH)
        speed *= -1;
    this->speed = speed;
    this->big_wire = big_wire;
    this->upside_down = upside_down;
}

void Wire::update(float dt) {
    Sprite::update(dt);
    
    velocity.x = speed;
    
    if(limit.x < GAME_WIDTH) {
        if(position.x < limit.x) {
            Destroy();
        }
    }
    
    if(limit.x > GAME_WIDTH) {
        if(position.x > limit.x) {
            Destroy();
        }
    }
}