#include <iostream>
#include <cmath>
#include <memory>
#include "spade.h"
#include "StartScene.h"
#include "MenuScene.h"

int main(){
    InitSpadeWindow(1280, 720, 640, 360, "game", FLAG_WINDOW_RESIZABLE);
    RenderTexture2D target = LoadRenderTexture(GAME_WIDTH, GAME_HEIGHT);
    SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);
    float scale = 0;
    
    // ======================================================== START ========================================================= //
    SceneManager manager;
    manager.add(std::make_unique<MenuScene>());
    manager.add(std::make_unique<StartScene>());
    
    while(!WindowShouldClose()) {
    // ======================================================== UPDATE ======================================================== //
        scale = std::min((float)GetScreenWidth()/GAME_WIDTH, (float)GetScreenHeight()/GAME_HEIGHT);
        manager.update(GetFrameTime());
        
    // ========================================================= DRAW ========================================================= //
        BeginTextureMode(target);
            ClearBackground(Color{66, 57, 82, 255});
            manager.draw();
        EndTextureMode();
        
        DrawLetterBox(target, scale, GAME_WIDTH, GAME_HEIGHT);
    }
    
    manager.UnloadScenes();
    CloseWindow();
}