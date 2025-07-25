#pragma once
#include <iostream>
#include <cmath>
#include "spade.h"
#include "player.h"
#include "wire.h"
#include "wire_manager.h"
#include "score_manager.h"
#include "level_manager.h"

class CutScene : public Scene
{
private:
    
public:
    Sprite* tut_sprite;
    int cnt;
    
    void start() override {
        CameraSetup();
        camera.zoom = 3;
        
        tut_sprite = new Sprite(240, 135);
        tut_sprite->loadTexture(RESOURCES_PATH "tut_0.png");
        add(tut_sprite);
        
        cnt = 0;
        Scene::start();
    }
    
    void update(float dt) override {
        Scene::update(dt);
        // Your code here
        
        if(IsKeyPressed(KEY_SPACE) && cnt == 3) {
            UnloadTexture(tut_sprite->texture);
            manager->SwitchScene(2);
            cnt++;
        }
        if(IsKeyPressed(KEY_SPACE) && cnt == 2) {
            cnt++;
        }
        if(IsKeyPressed(KEY_SPACE) && cnt == 1) {
            UnloadTexture(tut_sprite->texture);
            tut_sprite->loadTexture(RESOURCES_PATH "tut_2.png");
            cnt++;
        }
        if(IsKeyPressed(KEY_SPACE) && cnt == 0) {
            UnloadTexture(tut_sprite->texture);
            tut_sprite->loadTexture(RESOURCES_PATH "tut_1.png");
            cnt++;
        }
    }
    
    void draw() override {
        BeginMode2D(camera);
            Scene::draw();
            
            DrawText("space to continue...", 322, 230, 0.1f, Color{113, 63, 82, 255});
            if(cnt == 0) {
                DrawText("Make kitty hit wall", GAME_WIDTH/2 - (TextLength("Make kitty hit wall")+1)*6/2 + 16, 208, 6, WHITE);
            }
            if(cnt == 1) {
                DrawText("Then the other wall", GAME_WIDTH/2 - (TextLength("Make kitty hit wall")+1)*6/2 + 16, 208, 6, WHITE);
            }
            if(cnt == 2) {
                DrawText("Wall make score big", GAME_WIDTH/2 - (TextLength("Make kitty hit wall")+1)*6/2 + 16, 208, 6, WHITE);
            }
            if(cnt == 3) {
                DrawText("Good luck pawdawan :3", GAME_WIDTH/2 - (TextLength("Make kitty hit wall")+1)*6/2 + 8, 208, 6, WHITE);
            }
        EndMode2D();
    }
};
