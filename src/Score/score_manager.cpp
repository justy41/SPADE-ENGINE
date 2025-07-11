#include "score_manager.h"

ScoreManager::ScoreManager(Player* player) : Object(0, 0) {
    score = 0;
    this->player = player;
}

void ScoreManager::update(float dt) {
    if(player != nullptr) {
        if(player->touched_right || player->touched_left) {
            score++;
            // TODO: add the yellow bars at the edges of the screen when hit by the player
        }
    }
}

void ScoreManager::draw() {
    DrawText(std::to_string(score).c_str(), 10, 10, 24, BLUE);
}

void ScoreManager::reset_score() {
    score = 0;
}