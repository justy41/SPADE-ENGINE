#include "score_manager.h"

ScoreManager::ScoreManager(Player* player, int max_score) : Object(0, 0) {
    score = 0;
    prev_score = score;
    this->player = player;
    this->max_score = max_score;
    space_cooldown = 2.f;
}

void ScoreManager::update(float dt) {
    if(score >= max_score) {
        won = true;
    }
    else {
        if(player != nullptr) {
            if(player->touched_right || player->touched_left) {
                score++;
                // TODO: add the yellow bars at the edges of the screen when hit by the player
            }
            
            if(player->hit) {
                score /= 2;
                dif_score = prev_score - score;
                player->hit = false;
            }
        }
        else {
            std::cout<<"\n\n WARNING: player is nullptr \n\n";
        }
        
        prev_score = score;
    }
    
    if(won) {
        space_cooldown -= dt;
    }
}

void ScoreManager::draw() {
    DrawText(std::to_string(score).c_str(), 10, 10, 24, BLUE);
    DrawText(std::string("reach ").append(std::to_string(max_score).c_str()).c_str(), 8, 34, 8, YELLOW);
    
    if(player->immune) {
        std::string difference_text = "-";
        difference_text.append(std::to_string(dif_score));
        if(!won)
            DrawText(difference_text.c_str(), 40, 10, 24, RED);
    }
    
    if(won) {
        DrawRectangle(-10, -10, GAME_WIDTH+10, GAME_HEIGHT+10, Color{252, 186, 3, 30});
        DrawText("YOU WON", GAME_WIDTH/2 - (TextLength("YOU WON")+1)*17/2, GAME_HEIGHT/2 - 17, 34, WHITE);
        if(space_cooldown <= 0)
            DrawText("Press space to return to menu", GAME_WIDTH/2 - (TextLength("Press space to return to menu")+1)*6/2, GAME_HEIGHT/2 + 26, 12, WHITE);
    }
}

void ScoreManager::reset_score() {
    score = 0;
}