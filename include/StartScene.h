#pragma once
#include <iostream>
#include <cmath>
#include "spade.h"
#include "player.h"

class StartScene : public Scene
{
private:
    
public:
    Player* player;
    
    void start() override {
        CameraSetup();
        
        player = new Player(100, 100, 1200, -400);
        player->loadTexture(RESOURCES_PATH "square.png", true);
        player->drag = Vector2{55, 300};
        add(player);
        
        Scene::start();
    }
    
    void update(float dt) override {
        Scene::update(dt);
        // Your code here
    }
    
    void draw() override {
        BeginMode2D(camera);
            Scene::draw();
        EndMode2D();
    }
};
