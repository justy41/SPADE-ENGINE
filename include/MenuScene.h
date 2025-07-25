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
    Sprite* lock_medium;
    Sprite* lock_hard;
    LevelManager* level_manager;
    
    float thanks_cooldown = 2;
    
    void start() override {
        CameraSetup();
        
        easy_mode = new Sprite(176, 144);
        easy_mode->loadTexture(RESOURCES_PATH "easy.png");
        add(easy_mode);
        
        medium_mode = new Sprite(288, 144);
        medium_mode->loadTexture(RESOURCES_PATH "medium.png");
        add(medium_mode);
        
        lock_medium = new Sprite(288 - 4, 144 - 4);
        lock_medium->loadTexture(RESOURCES_PATH "locked.png");
        add(lock_medium);
        
        hard_mode = new Sprite(400, 144);
        hard_mode->loadTexture(RESOURCES_PATH "hard.png");
        add(hard_mode);
        
        lock_hard = new Sprite(400 - 4, 144 - 4);
        lock_hard->loadTexture(RESOURCES_PATH "locked.png");
        add(lock_hard);
        
        level_manager = new LevelManager();
        add(level_manager);
        
        Scene::start();
    }
    
    void update(float dt) override {
        Scene::update(dt);
        
        if(lock_1)
            lock_medium->Destroy();
        if(lock_2) {
            lock_hard->Destroy();
        }
        
        // Your code here
        if(IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
            if(slot_index == 0) {
                manager->SwitchScene(2);
            }
            else if(slot_index == 1 && lock_1) {
                manager->SwitchScene(3);
            }
            else if(slot_index == 2 && lock_2) {
                manager->SwitchScene(4);
            }
        }
        
        // std::cout<<level_manager->slot_index<<" ";
    }
    
    void draw() override {
        BeginMode2D(camera);
            Scene::draw();
            DrawText("Esc to quit game", 5, 5, 8, Color{133, 69, 82, 255});
            DrawText("Level Select", GAME_WIDTH/2-TextLength("Level Select")*12/2, 90, 24, WHITE);
            
            if(finished_game) {
                thanks_cooldown -= GetFrameTime();
                DrawText("Congratulations! YOU ROCK!", 80, 272, 34, Color{209, 191, 176, 255});
                if(thanks_cooldown <= 0)
                    DrawText("Thanks for playing :)", 248, 320, 14, Color{209, 191, 176, 255});
            }
        EndMode2D();
    }
};
