#include "level_manager.h"

LevelManager::LevelManager() : Object(0, 0) {
    
}

void LevelManager::create() {
    slot_index = 0;
    level_count = 3;
    slot_change = false;
    
    arrow = new Sprite(192, 224);
    arrow->loadTexture(RESOURCES_PATH "arrow.png");
    parent_scene->add(arrow);
}

void LevelManager::update(float dt) {
    if(IsKeyPressed(KEY_D)) {
        slot_index++;
        slot_change = true;
        arrow->position.x += 112;
    }
    if(IsKeyPressed(KEY_A)) {
        slot_index--;
        slot_change = true;
        arrow->position.x -= 112;
    }
    
    if(slot_index < 0) {
        slot_index = level_count-1;
    }
    
    slot_index = slot_index%3;
    
    if(slot_change) {
        slot_change = false;
    }
    
    if(slot_index == 0) {
        arrow->position.x = 192;
    }
    if(slot_index == level_count-1) {
        arrow->position.x = 192 + (112*slot_index);
    }
}

void LevelManager::draw() {
    
}