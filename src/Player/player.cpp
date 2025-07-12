#include "player.h"

Player::Player(float x, float y, float acc, float jumpForce, float gravityForce, float fallMultiplier) : Sprite(x, y),
    acc(acc),
    jumpForce(jumpForce),
    gravityForce(gravityForce),
    fallMultiplier(fallMultiplier)
{
    touched_left = false;
    touched_right = false;
    can_touch_left = true;
    can_touch_right = true;
    immune = false;
    hit = false;
    
    immunity_timer_value = 2;
    immunity_timer = immunity_timer_value;
}

void Player::update(float dt) {
    Sprite::update(dt);
    
    if(immune) {
        immunity_timer -= dt;
    }
    if(immunity_timer <= 0) {
        immune = false;
        immunity_timer = immunity_timer_value;
    }
    
    // ============================= This block...
    if(!can_touch_right) {
        touched_right = false;
    }
    
    if(!can_touch_left) {
        touched_left = false;
    }
    // =============================
    
    SetPlayerBounds(); // ========== ...before this!
    RotatePlayer(10, dt);
    
    if(collisions["down"]) {
        SetGravity(0);
    }
    else {
        SetGravity(gravityForce);
        if(velocity.y > 0) {
            SetGravity(gravityForce*fallMultiplier);
        }
    }
    
    // Sets the camera zoom
    if(IsKeyPressed(KEY_Z)) {
        camera->zoom = 0.5f;
    }
    
    if(IsKeyDown(KEY_D)) {
        acceleration.x = acc;
    }
    else if(IsKeyDown(KEY_A)) {
        acceleration.x = -acc;
    }
    else {
        acceleration.x = 0;
    }
    
    if(IsKeyPressed(KEY_SPACE)) {
        velocity.y = jumpForce;
    }
}

void Player::draw() {
    Sprite::draw();
}

void Player::on_collision(Base* other) {
    if(!immune) {
        if(other->tag == "Wire") {
            immune = true;
            hit = true;
            parent_scene->pause(0.09f);
        }
    }
}

void Player::SetPlayerBounds()
{
    // Setting bounds on the Y axis
    if(position.y + hitbox.height/2.f >= GAME_HEIGHT) {
        acceleration.y = 0;
        velocity.y *= -1; // Change this to 0 to make it just stay on the ground
        position.y = GAME_HEIGHT - hitbox.height/2.f;
    }
    else if(position.y <= 0) {
        acceleration.y = 0;
        velocity.y *= -1;
        position.y = 0 - offset.y;
    }
    else {
        SetGravity(gravityForce);
        if(velocity.y > 0) {
            SetGravity(gravityForce*fallMultiplier);
        }
    }
    
    // Setting bounds on the X axis
    if(position.x + hitbox.width/2.f >= GAME_WIDTH) {
        acceleration.x = 0;
        velocity.x *= -1;
        position.x = GAME_WIDTH - hitbox.width/2.f;
        
        if(can_touch_right) {
            touched_right = true;
            can_touch_right = false;
            can_touch_left = true;
        }
    }
    if(position.x + offset.x <= 0) {
        acceleration.x = 0;
        velocity.x *= -1;
        position.x = 0 - offset.x;
        
        if(can_touch_left) {
            touched_left = true;
            can_touch_left = false;
            can_touch_right = true;
        }
    }
}

void Player::RotatePlayer(float degrees_per_frame, float dt) {
    if(velocity.x > 0) {
        rotation += degrees_per_frame + (velocity.x * dt);
    }
    if(velocity.x < 0) {
        rotation -= degrees_per_frame - (velocity.x * dt);
    }
    
    if(rotation >= 360) {
        rotation = rotation - 360;
    }
}

void Player::SetGravity(float g) {
    gravity = g;
}
