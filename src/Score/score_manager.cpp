#include "score_manager.h"

ScoreManager::ScoreManager(Player* player) : Object(0, 0) {
    score = 0;
    prev_score = score;
    this->player = player;
}

void ScoreManager::update(float dt) {
    if(player != nullptr) {
        if(player->touched_right || player->touched_left) {
            score++;
            // TODO: add the yellow bars at the edges of the screen when hit by the player
        }
        
        if(player->hit) {
            score /= 3;
            dif_score = prev_score - score;
            player->hit = false;
        }
    }
    else {
        std::cout<<"\n\n YOYOYO\n\n";
    }
    
    prev_score = score;
}

void ScoreManager::draw() {
    DrawText(std::to_string(score).c_str(), 10, 10, 24, BLUE);
    if(player->immune) {
        std::string difference_text = "-";
        difference_text.append(std::to_string(dif_score));
        DrawText(difference_text.c_str(), 40, 10, 24, RED);
    }
}

void ScoreManager::reset_score() {
    score = 0;
}