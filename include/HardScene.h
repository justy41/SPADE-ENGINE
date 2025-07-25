#pragma once
#include <iostream>
#include <cmath>
#include "spade.h"
#include "player.h"
#include "wire.h"
#include "wire_manager.h"
#include "score_manager.h"

class HardScene : public Scene
{
private:
    
public:
    Player* player;
    WireManager* wire_manager;
    ScoreManager* score_manager;
    Sprite* yellow_bar;
    
    void start() override {
        CameraSetup();
        
        yellow_bar = new Sprite(0, 0);
        yellow_bar->loadTexture(RESOURCES_PATH "yellow_bar.png");
        add(yellow_bar);
        
        player = new Player(100, 100, 1200, -400);
        player->loadTexture(RESOURCES_PATH "player.png", true);
        player->set_tag("Player");
        player->drag = Vector2{55, 300};
        player->set_hitbox(6, 6, 14, 14);
        add(player);
        
        wire_manager = new WireManager(1, 60, 125);
        add(wire_manager);
        
        score_manager = new ScoreManager(player, 30);
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
            finished_game = true;
            if(IsKeyPressed(KEY_SPACE) && score_manager->space_cooldown <= 0) {
                manager->SwitchScene(1);
            }
        }
    }
    
    void draw() override {
        ClearBackground(Color{120, 57, 90, 255});
        BeginMode2D(camera);
            Scene::draw();
        EndMode2D();
    }
};
