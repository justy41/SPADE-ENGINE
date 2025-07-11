#pragma once
#include <iostream>
#include <cmath>
#include "spade.h"
#include "player.h"
#include "wire.h"
#include "wire_manager.h"
#include "score_manager.h"

class StartScene : public Scene
{
private:
    
public:
    Player* player;
    WireManager* wire_manager;
    ScoreManager* score_manager;
    
    void start() override {
        CameraSetup();
        
        player = new Player(100, 100, 1200, -400);
        player->loadTexture(RESOURCES_PATH "player.png", true);
        player->set_tag("Player");
        player->drag = Vector2{55, 300};
        player->set_hitbox(6, 6, 14, 14);
        add(player);
        
        wire_manager = new WireManager(3);
        add(wire_manager);
        
        score_manager = new ScoreManager(player);
        add(score_manager);
        
        Scene::start();
    }
    
    void update(float dt) override {
        Scene::update(dt);
        // Your code here
        // std::cout<<members.size()<<" ";
    }
    
    void draw() override {
        BeginMode2D(camera);
            Scene::draw();
        EndMode2D();
    }
};
