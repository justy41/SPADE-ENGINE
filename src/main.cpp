#include <iostream>
#include <cmath>
#include <memory>
#include "spade.h"
#include "raymath.h"
#include "CutScene.h"
#include "MenuScene.h"
#include "EasyScene.h"
#include "MediumScene.h"
#include "HardScene.h"

int main(){
    InitSpadeWindow(1280, 720, 640, 360, "game", FLAG_WINDOW_RESIZABLE);
    RenderTexture2D target = LoadRenderTexture(GAME_WIDTH, GAME_HEIGHT);
    SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);
    float scale = 0;
    Color Quit_color = Color{255, 255, 255, 0};
    bool exitWindow = false;
    
    // ======================================================== START ========================================================= //
    SceneManager manager;
    manager.add(std::make_unique<MenuScene>());
    manager.add(std::make_unique<EasyScene>());
    manager.add(std::make_unique<MediumScene>());
    manager.add(std::make_unique<HardScene>());
    manager.add(std::make_unique<CutScene>());
    
    while(!SpadeWindowShouldClose(2) && !exitWindow) {
    // ======================================================== UPDATE ======================================================== //
        if(WindowShouldClose() && !IsKeyPressed(KEY_ESCAPE)) exitWindow = true;
        
        scale = std::min((float)GetScreenWidth()/GAME_WIDTH, (float)GetScreenHeight()/GAME_HEIGHT);
        manager.update(GetFrameTime());
        
    // ========================================================= DRAW ========================================================= //
        BeginTextureMode(target);
            ClearBackground(Color{66, 57, 82, 255});
            manager.draw();
            
            // QUITTING text appearance
            if(IsKeyDown(KEY_ESCAPE)) {
                Quit_color = ColorLerp(Quit_color, WHITE, GetFrameTime()*2);
                DrawText("quitting. . .", 5, GAME_HEIGHT-20, 15.5f, Quit_color);
            }
            else {
                Quit_color.a = 0;
            }
        EndTextureMode();
        
        DrawLetterBox(target, scale, GAME_WIDTH, GAME_HEIGHT);
    }
    
    manager.UnloadScenes();
    CloseWindow();
}