#pragma once
#include <iostream>
#include <cmath>
#include "spade.h"
#include "level_manager.h"

class MenuScene : public Scene
{
private:
    
public:
    Sprite* easy_mode;
    Sprite* medium_mode;
    Sprite* hard_mode;
    LevelManager* level_manager;
    
    void start() override {
        CameraSetup();
        
        easy_mode = new Sprite(176, 144);
        easy_mode->loadTexture(RESOURCES_PATH "easy.png");
        add(easy_mode);
        
        medium_mode = new Sprite(288, 144);
        medium_mode->loadTexture(RESOURCES_PATH "medium.png");
        add(medium_mode);
        
        hard_mode = new Sprite(400, 144);
        hard_mode->loadTexture(RESOURCES_PATH "hard.png");
        add(hard_mode);
        
        level_manager = new LevelManager();
        add(level_manager);
        
        Scene::start();
    }
    
    void update(float dt) override {
        Scene::update(dt);
        
        // Your code here
        if(IsKeyPressed(KEY_ENTER)) {
            manager->SwitchScene(2);
        }
    }
    
    void draw() override {
        BeginMode2D(camera);
            Scene::draw();
            DrawText("Level Select", GAME_WIDTH/2-TextLength("Level Select")*12/2, 90, 24, WHITE);
        EndMode2D();
    }
};
