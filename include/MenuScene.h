#pragma once
#include <iostream>
#include <cmath>
#include "spade.h"

class MenuScene : public Scene
{
private:
    
public:
    
    void start() override {
        CameraSetup();
        
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
            DrawText("Main Menu", 100, 100, 24, WHITE);
        EndMode2D();
    }
};
