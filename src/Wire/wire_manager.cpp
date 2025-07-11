#include "wire_manager.h"

WireManager::WireManager(float in_between_spawn_time) : Object(0, 0) {
    spawn_timer = in_between_spawn_time;
    spawn_timer_value = in_between_spawn_time;
}

void WireManager::update(float dt) {
    spawn_timer -= dt;
    if(spawn_timer <= 0) {
        spawn_timer = spawn_timer_value;
        
        Wire* wire = new Wire(GetRandomValue(0, 1), GetRandomValue(65, 120), GetRandomValue(50, 120), GetRandomValue(false, true), GetRandomValue(false , true));
        
        if(wire->upside_down) {
            wire->position.y = GetRandomValue(-190, -100);
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
            if(wire->upside_down)
                wire->loadTexture(RESOURCES_PATH "big_wire_flipped.png");
            else
                wire->loadTexture(RESOURCES_PATH "big_wire.png");
        }
        else {
            if(wire->upside_down)
                wire->loadTexture(RESOURCES_PATH "small_wire_flipped.png");
            else
                wire->loadTexture(RESOURCES_PATH "small_wire.png");
        }
        
        parent_scene->add(wire);
    }
}
