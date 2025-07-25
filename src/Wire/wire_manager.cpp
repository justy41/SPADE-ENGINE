#include "wire_manager.h"

WireManager::WireManager(float in_between_spawn_time, float minSpeed, float maxSpeed) : Object(0, 0) {
    spawn_timer = in_between_spawn_time;
    spawn_timer_value = in_between_spawn_time;
    this->minSpeed = minSpeed;
    this->maxSpeed = maxSpeed;
}

void WireManager::update(float dt) {
    spawn_timer -= dt;
    if(spawn_timer <= 0) {
        spawn_timer = spawn_timer_value;
        
        Wire* wire = new Wire(GetRandomValue(0, 1), GetRandomValue(170, 210), GetRandomValue(minSpeed, maxSpeed), GetRandomValue(false, true), GetRandomValue(false , true));
        
        if(wire->upside_down) {
            wire->position.y = GetRandomValue(-230, -200);
        }
        
        if(wire->position.x == 0) {
            wire->position.x = -20;
            wire->limit.x = GAME_WIDTH + 10;
        }
        if(wire->position.x == 1) {
            wire->position.x = 655;
            wire->limit.x = -20;
            wire->speed *= -1;
        }
        
        if(wire->position.y == 0) {
            wire->position.y = -20;
            wire->limit.y = GAME_HEIGHT + 10;
        }
        if(wire->position.y == 1) {
            wire->position.y = 655;
            wire->limit.y = -20;
            wire->speed *= -1;
        }
        
        if(wire->big_wire) {
            if(wire->upside_down) {
                wire->loadTexture(RESOURCES_PATH "big_wire_flipped.png");
                wire->set_hitbox(8, -5, 10, 320);
            }
            else {
                wire->loadTexture(RESOURCES_PATH "big_wire.png");
                wire->set_hitbox(9, 10, 10, 295);
            }
        }
        else {
            if(wire->upside_down)
                wire->loadTexture(RESOURCES_PATH "small_wire_flipped.png");
            else
                wire->loadTexture(RESOURCES_PATH "small_wire.png");
            wire->set_hitbox(2, 13, 7, 293);
        }
        
        wire->set_tag("Wire");
        
        parent_scene->add(wire);
    }
}
