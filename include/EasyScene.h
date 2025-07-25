#pragma once
#include <iostream>
#include <cmath>
#include "spade.h"
#include "player.h"
#include "wire.h"
#include "wire_manager.h"
#include "score_manager.h"
#include "level_manager.h"

class EasyScene : public Scene
{
private:
    
public:
    Player* player;
    Sprite* yellow_bar;
    WireManager* wire_manager;
    ScoreManager* score_manager;
    
    void start() override {
        CameraSetup();
        
        yellow_bar = new Sprite(0, 0);
        yellow_bar->loadTexture(RESOURCES_PATH "yellow_bar.png");
        add(yellow_bar);
        
        player = new Player(100, 100, 1200, -400, 640.f, 1.5f);
        player->loadTexture(RESOURCES_PATH "player.png", true);
        player->set_tag("Player");
        player->drag = Vector2{55, 300};
        player->set_hitbox(6, 6, 14, 14);
        add(player);
        
        wire_manager = new WireManager(3, 50, 120);
        add(wire_manager);
        
        score_manager = new ScoreManager(player, 20);
        add(score_manager);
        
        Scene::start();
    }
    
    void update(float dt) override {
        Scene::update(dt);
        // Your code here
        // std::cout<<members.size()<<" ";
        
        if(player->touched_left) {
            yellow_bar->position.x = GAME_WIDTH - yellow_bar->texture.width;
        }
        if(player->touched_right) {
            yellow_bar->position.x = 0;
        }
        
        if(score_manager->won) {
            lock_1 = true;
            if(IsKeyPressed(KEY_SPACE)) {
                manager->SwitchScene(1);
            }
        }
    }
    
    void draw() override {
        BeginMode2D(camera);
            Scene::draw();
        EndMode2D();
    }
};
