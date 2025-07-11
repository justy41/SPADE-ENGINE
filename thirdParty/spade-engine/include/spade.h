// ============================================================= SPADE ENGINE ============================================================= //

#pragma once
#include <iostream>
#include <cmath>
#include <vector>
#include <cstring>
#include <string>
#include <unordered_map>
#include <memory>
#include <utility>
#include "raylib.h"
#include "imgui.h"
#include "LDtkLoader/Project.hpp"

inline int GAME_WIDTH = 640, GAME_HEIGHT = 360;

inline void InitSpadeWindow(int screenW, int screenH, int gameW, int gameH, const char* window_name, unsigned int configFlags = 0, unsigned int windowStateFlags = 0, int fps = 60){
    SetConfigFlags(configFlags);
    InitWindow(screenW, screenH, window_name);
    SetWindowState(windowStateFlags);
    
    GAME_WIDTH = gameW;
    GAME_HEIGHT = gameH;
    
    SetTargetFPS(fps);
}

// Stupid std::pair<float, float> hash function because C++ is too stupid to process anything...
struct FloatPairHash {
    std::size_t operator()(const std::pair<float, float>& p) const {
        std::size_t h1 = std::hash<float>{}(p.first);
        std::size_t h2 = std::hash<float>{}(p.second);
        // Combine hashes (e.g., using boost-style hash combine)
        return h1 ^ (h2 << 1);
    }
};

// Stupid Rectangle hash function because C++ is too stupid to process anything... again
struct RectangleHash {
    std::size_t operator()(const Rectangle& rect) const {
        std::size_t hx = std::hash<float>{}(rect.x);
        std::size_t hy = std::hash<float>{}(rect.y);
        std::size_t hw = std::hash<float>{}(rect.width);
        std::size_t hh = std::hash<float>{}(rect.height);

        // Combine hashes using a simple hash combining technique
        return ((hx ^ (hy << 1)) >> 1) ^ (hw << 1) ^ (hh << 2);
    }
};

inline std::vector<Vector2> NEIGHBOUR_OFFSETS = {
    Vector2{-1, 1},
    Vector2{0, 1},
    Vector2{1, 1},
    Vector2{-1, 0},
    Vector2{0, 0},
    Vector2{1, 0},
    Vector2{-1, -1},
    Vector2{0, -1},
    Vector2{1, -1}
};

class Scene;

class Base
{
private:
    
public:
    Scene* parent_scene;
    Camera2D* camera;
    
    bool active;
    bool destroy;
    
    Base() {}
    virtual void create() {}
    virtual void update(float dt) {}
    virtual void draw() {}
    // TODO: add OnCollision() functions that execute when colliding (like in GameMaker Studio 2)
    ~Base() {}
};

class SceneManager;

class Scene
{
private:
    ldtk::IntRect r;
    std::unordered_map<std::string, Texture2D> tilesets;
    bool ldtk_debug;
    
    std::vector<Base*> members_to_remove;
public:
    std::vector<Base*> members;
    
    SceneManager* manager;
    int sceneIndex;
    Vector2 VirtualMousePosition;
    float scale = 0;
    float offsetX, offsetY;
    
    Camera2D camera;
    
    ldtk::Project ldtkProject;
    const ldtk::World* world;
    const ldtk::Level* level_0;
    const ldtk::Layer* ground_layer;
    float tile_size = 0;
    std::unordered_map<std::pair<float, float>, bool, FloatPairHash> collisions_layer;
    std::unordered_map<std::string, Rectangle> entities;
    
    // Adds a heap allocated object in a std::vector<SineBasic*>
    //
    // NOTE: always create objects with 'new' when adding to a Group
    virtual void add(Base* obj) {
        obj->camera = &camera;
        obj->parent_scene = this;
        members.push_back(obj);
    }
    
    // Runs once when the Scene is loaded
    //
    // NOTE: put this as the first line if the function is overriden as Scene::start()
    virtual void start() {
        for(int i = 0; i<members.size(); i++) {
            if(members[i]->active) {
                members[i]->create();
            }
        }
    }
    
    // Runs every frame
    //
    // NOTE: put this as the first line if the function is overriden as Scene::update(dt)
    virtual void update(float dt) {
        scale = std::min((float)GetScreenWidth()/GAME_WIDTH, (float)GetScreenHeight()/GAME_HEIGHT);
        offsetX = ((float)GetScreenWidth() - (GAME_WIDTH * scale)) * 0.5f;
        offsetY = ((float)GetScreenHeight() - (GAME_HEIGHT * scale)) * 0.5f;
        VirtualMousePosition.x = ((GetMouseX() - offsetX) / scale);
        VirtualMousePosition.y = ((GetMouseY() - offsetY) / scale);
        
        for(int i = 0; i<members.size(); i++) {
            if(members[i]->active) {
                members[i]->update(dt);
                if(members[i]->destroy)
                    members_to_remove.push_back(members[i]);
            }
        }
        
        for(auto obj : members_to_remove) {
            auto it = std::find(members.begin(), members.end(), obj);
            if(it != members.end()) {
                delete *it;
                members.erase(it);
            }
        }
        
        members_to_remove.clear();
    }
    
    // Runs every frame
    //
    // NOTE: put this depending of the draw order as Scene::draw()
    virtual void draw() {
        for(int i = 0; i<members.size(); i++) {
            if(members[i]->active) {
                members[i]->draw();
            }
        }
    }
    
    // Make the camera follow a position
    void CameraFollow(Vector2 pos) {
        camera.target = Vector2{std::round(pos.x), std::round(pos.y)};
    }
    
    void CameraSetup() {
        camera = {0};
        camera.target = Vector2{GAME_WIDTH/2.f, GAME_HEIGHT/2.f};
        camera.offset = Vector2{GAME_WIDTH/2.f, GAME_HEIGHT/2.f};
        camera.rotation = 0;
        camera.zoom = 1;
    }
    
    // Loads a LDtk map
    //
    // NOTE: tilesets are loaded relative to the file path of the .ldtk file. File paths can be found in the .ldtk file.
    // The tileset paths are printed in the command line to see.
    //
    // NOTE: in LDtk the entities need to have a CUSTOM FIELD called "Name" <- exactly written like this for it to work
    void LoadLDtkMap(const char* tilemap_path, float fixed_tile_size, std::vector<std::string> collision_layer_names) {
        ldtkProject.loadFromFile(tilemap_path);
        world = &ldtkProject.getWorld();
        
        tile_size = fixed_tile_size;
        for(const auto& level : world->allLevels()) {
            if(!collision_layer_names.empty()) {
                for(auto name : collision_layer_names) {
                    for(const auto& tile : level.getLayer(name).allTiles()) {
                        collisions_layer.insert({std::make_pair(tile.getGridPosition().x + level.position.x/tile_size, tile.getGridPosition().y + level.position.y/tile_size), true});
                    }
                }
            }
            else break;
        }
        
        // This block of code takes the tilemap_path and erases the map.ldtk part.
        // After that, the tileset path from the ldtk layer is appended to it, forming the path to the tileset.
        // EXAMPLE: tilemaps/map.ldtk + ../tilesets/tileset_1.png = tilemaps/../tilesets/tileset_1.png
        //
        // The entities are also extracted in an unordered_map for later use.
        for(const auto& level : world->allLevels()) {
            for(const auto& layer : level.allLayers()) {
                if(layer.getType() != ldtk::LayerType::Entities) {
                    if(tilesets.find(layer.getTileset().name) == tilesets.end()) {
                        std::string texture_file_name = layer.getTileset().path; // Load file path relative to the .ldtk file
                        std::string map_path = tilemap_path;
                        for(int i = map_path.size()-1; i>=0; i--) {
                            if(map_path[i-1] == '/') {      // When the '/' is next...
                                map_path.erase(i);          // ...then erase.
                                break;
                            }
                        }
                        
                        map_path.append(texture_file_name); // Combine the two file paths.
                        tilesets.insert({layer.getTileset().name, LoadTexture(map_path.c_str())}); // Insert the name and load the tileset.
                        std::cout<<"\nTILESET PATH:\n"<<map_path<<"\n\n";
                    }
                }
                else {
                    // Saving ldtk entities as an element with Name, Position and Size in an unordered_map
                    for(const auto& ent : layer.allEntities()) {
                        entities.insert({
                            ent.getField<std::string>("Name").value(),
                            Rectangle{
                                (float)ent.getPosition().x + level.position.x,
                                (float)ent.getPosition().y + level.position.y,
                                (float)ent.getSize().x,
                                (float)ent.getSize().y
                            }
                        });
                    }
                }
            }
        }
    }
    
    Rectangle getLDtkEntity(std::string Name_field) {
        Rectangle rect = Rectangle{0, 0, 0, 0};
        if(entities[Name_field].width != 0) {
            rect = Rectangle{entities[Name_field].x, entities[Name_field].y, entities[Name_field].width, entities[Name_field].height};
            return rect;
        }
        return rect;
    }
    
    // Draws the entire LDtk map
    void DrawLDtkMap() {
        for(const auto& level : world->allLevels()) {
            for(int i = level.allLayers().size()-1; i>=0; i--) { // Reversed order because LDtkLoader takes the layers inverted.
                if(level.allLayers()[i].getType() != ldtk::LayerType::Entities) {
                    std::string ts_name = level.allLayers()[i].getTileset().name; // Get the tileset name of the current layer.
                    if(level.allLayers()[i].isVisible()) {
                        for(const auto& tile : level.allLayers()[i].allTiles()) { // Draw all tiles based on their source rect.
                            r = tile.getTextureRect(); // source rect
                            DrawTextureRec(
                                tilesets[ts_name],
                                Rectangle{(float)r.x, (float)r.y, (float)r.width, (float)r.height},
                                Vector2{(float)tile.getPosition().x + level.position.x, (float)tile.getPosition().y + level.position.y},
                                WHITE
                            );
                        }
                    }
                }
            }
        }
    }
    
    // Draws only the named level
    void DrawLDtkLevel(const char* level_name) {
        for(int i = world->getLevel(level_name).allLayers().size()-1; i>=0; i--) {
            if(world->getLevel(level_name).allLayers()[i].getType() != ldtk::LayerType::Entities) {
                std::string ts_name = world->getLevel(level_name).allLayers()[i].getTileset().name;
                if(world->getLevel(level_name).allLayers()[i].isVisible()) {
                    for(const auto& tile : world->getLevel(level_name).allLayers()[i].allTiles()) {
                        r = tile.getTextureRect();
                        DrawTextureRec(
                            tilesets[ts_name],
                            Rectangle{(float)r.x, (float)r.y, (float)r.width, (float)r.height},
                            Vector2{(float)tile.getPosition().x, (float)tile.getPosition().y},
                            WHITE
                        );
                    }
                }
            }
        }
    }
    
    // Draws a layer from all levels (exception is entities layer)
    void DrawLDtkLayer(const char* layer_name) {
        for(const auto& level : world->allLevels()) {
            std::string ts_name = level.getLayer(layer_name).getTileset().name;
            if(level.getLayer(layer_name).isVisible()) {
                for(const auto& tile : level.getLayer(layer_name).allTiles()) {
                    r = tile.getTextureRect();
                    DrawTextureRec(
                        tilesets[ts_name],
                        Rectangle{(float)r.x, (float)r.y, (float)r.width, (float)r.height},
                        Vector2{(float)tile.getPosition().x + level.position.x, (float)tile.getPosition().y + level.position.y},
                        WHITE
                    );
                }
            }
        }
    }
    
    // Toggle the LDtk map collision hitboxes if F6 key is pressed
    void DrawLDtkCollisionLayers() {
        if(IsKeyPressed(KEY_F6)) {
            ldtk_debug = !ldtk_debug;
        }
        
        if(ldtk_debug && !collisions_layer.empty()) {
            for(auto tile : collisions_layer) {
                DrawRectangleLinesEx(Rectangle{tile.first.first*tile_size, tile.first.second*tile_size, tile_size, tile_size}, 2, RED);
            }
        }
    }
    
    // ===================================================== LDTK MAP COLLISIONS ===================================================== //
    std::vector<Vector2> tiles_around(Vector2 pos, float tile_size, std::unordered_map<std::pair<float, float>, bool, FloatPairHash> collisions_layer) {
        std::vector<Vector2> tiles;
        Vector2 tile_loc = Vector2{std::floor(pos.x / tile_size), std::floor(pos.y / tile_size)};
        for(auto offset : NEIGHBOUR_OFFSETS) {
            Vector2 check_loc = Vector2{tile_loc.x + offset.x, tile_loc.y + offset.y};
            if(collisions_layer[std::make_pair(check_loc.x, check_loc.y)] == true) {
                tiles.push_back(check_loc);
            }
        }
        
        return tiles;
    }
    
    std::vector<Rectangle> physics_rects_around(Vector2 pos) {
        std::vector<Rectangle> rects;
        for(auto tile : tiles_around(pos, tile_size, collisions_layer)) {
            rects.push_back(Rectangle{tile.x*tile_size, tile.y*tile_size, tile_size, tile_size});
        }
        return rects;
    }
    
    /// @brief Gets the virtual X mouse position, dependend on the scale of the window
    /// @return 
    float GetVirtualMouseX() {
        return VirtualMousePosition.x;
    }
    /// @brief Gets the virtual Y mouse position, dependend on the scale of the window
    /// @return 
    float GetVirtualMouseY() {
        return VirtualMousePosition.y;
    }
    /// @brief Gets the virtual mouse position, dependend on the scale of the window
    /// @return 
    Vector2 GetVirtualMousePosition() {
        return VirtualMousePosition;
    }
    
    ~Scene() {
        
    }
};

class Object : public Base
{
private:
    
public:
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;
    Vector2 drag;
    Vector2 scale;
    Vector2 offset;
    Rectangle hitbox;
    float rotation;
    float gravity;
    
    bool solid;
    
    std::unordered_map<std::string, bool> collisions;
    
    Object(float x, float y) {
        position = Vector2{x, y};
        velocity = Vector2{0, 0};
        acceleration = Vector2{0, 0};
        drag = Vector2{0, 0};
        scale = Vector2{1, 1};
        offset = Vector2{0, 0};
        hitbox = Rectangle{x, y, 0, 0};
        rotation = 0;
        gravity = 0;
        
        active = true;
        solid = false;
        destroy = false;
        
        collisions.insert({{"right", false}, {"left", false}, {"down", false}, {"up", false}});
    }
    
    void set_scale(float scaleX, float scaleY) {
        scale = Vector2{scaleX, scaleY};
    }
    
    void apply_drag(float dt) {
        if(drag.x != 0) {
            velocity.x = MoveTowards(velocity.x, 0, drag.x * dt);
        }
        if(drag.y != 0) {
            velocity.y = MoveTowards(velocity.y, 0, drag.y * dt);
        }
    }
    
    // Increases or decreases a value until the end by an amount (usually with deltaTime)
    float MoveTowards(float start, float end, float amount) {
        if(start < end) return std::fmin(start + amount, end);
        if(start > end) return std::fmax(start - amount, end);
        return end;
    }
    
    void set_hitbox(float offsetX, float offsetY, float sizeX, float sizeY) {
        offset = Vector2{offsetX, offsetY};
        hitbox = Rectangle{position.x + offsetX, position.y + offsetY, sizeX, sizeY};
    }
    
    virtual void create() {}
    virtual void update(float dt) {
        collisions["right"] = false;
        collisions["left"] = false;
        collisions["down"] = false;
        collisions["up"] = false;
        
        apply_drag(dt);
        
        velocity.x += acceleration.x * dt;
        position.x += velocity.x * dt;
        
        // ================================================ COLLISION RESOLUTION X ================================================ //
        hitbox.x = position.x + offset.x;
        if(solid) {
            for(Rectangle rect : parent_scene->physics_rects_around(position)) {
                if(CheckCollisionRecs(hitbox, rect)) {
                    if(velocity.x > 0) {
                        hitbox.x = rect.x - hitbox.width;
                        collisions["right"] = true;
                    }
                    if(velocity.x < 0) {
                        hitbox.x = rect.x + rect.width;
                        collisions["left"] = true;
                    }
                    position.x = hitbox.x - offset.x;
                }
            }
        }
        
        if(collisions["right"] || collisions["left"]) {
            velocity.x = 0;
        }
        // ======================================================================================================================== //
        
        acceleration.y = gravity;
        velocity.y += acceleration.y * dt;
        position.y += velocity.y * dt;
        
        // ================================================ COLLISION RESOLUTION Y ================================================ //
        hitbox.y = position.y + offset.y;
        if(solid) {
            for(Rectangle rect : parent_scene->physics_rects_around(position)) {
                if(CheckCollisionRecs(hitbox, rect)) {
                    if(velocity.y > 0) {
                        hitbox.y = rect.y - hitbox.height;
                        collisions["down"] = true;
                    }
                    if(velocity.y < 0) {
                        hitbox.y = rect.y + rect.height;
                        collisions["up"] = true;
                    }
                    position.y = hitbox.y - offset.y;
                }
            }
        }
        
        if(collisions["down"] || collisions["up"]) {
            velocity.y = 0;
        }
        // ======================================================================================================================== //
    }
    virtual void draw() {}
    void Destroy() {destroy = true;}
    ~Object() {}
};

class Sprite : public Object
{
private:
    bool debug_mode = false;
public:
    Texture2D texture;
    Vector2 origin;
    Color tint = WHITE;
    
    bool centered;
    bool hasTexture = false;
    
    Sprite(float x, float y) : Object(x, y) {
        
    }
    
    void loadTexture(const char* texture_path, bool centered = false) {
        texture = LoadTexture(texture_path);
        set_hitbox(0, 0, texture.width, texture.height);
        this->centered = centered;
        hasTexture = true;
    }
    
    void set_tint(Color color) {
        tint = color;
    }
    
    void create() override {
        Object::create();
        
        if(centered) {
            offset.x -= texture.width * scale.x /2.f;
            offset.y -= texture.height * scale.y /2.f;
        }
    }
    
    void draw() override {
        if(hasTexture) {
            Rectangle source = Rectangle{0, 0, (float)texture.width, (float)texture.height};
            Rectangle dest = Rectangle{position.x, position.y, (float)texture.width * scale.x, (float)texture.height * scale.y};
            if(centered) {
                origin = Vector2{texture.width * scale.x / 2.f, texture.height * scale.y / 2.f};
            }
            else {
                origin = Vector2{0, 0};
            }
            
            DrawTexturePro(
                texture,
                source,
                dest,
                origin,
                rotation,
                tint
            );
        }
        
        if(IsKeyPressed(KEY_T)) {
            debug_mode = !debug_mode;
        }
        
        if(debug_mode) {
            // DrawRectangleRec(hitbox, RED);
            DrawRectangleLinesEx(hitbox, 1, RED);
            DrawCircleLines(position.x, position.y, 3, GREEN);
        }
        
        Object::draw();
    }
    
    ~Sprite() {
        UnloadTexture(texture);
    }
};

inline bool overlap(Object* entA, Object* entB) {
    if(CheckCollisionRecs(entA->hitbox, entB->hitbox)) {
        return true;
    }
    return false;
}

// Stores a unique pointer and a factory function (lambda function)
struct StoredScene {
    std::unique_ptr<Scene> instance;
    std::function<std::unique_ptr<Scene>()> recreate;
    int sceneIndex;
};

class SceneManager
{
private:
    std::vector<StoredScene> scenes;
public:
    SceneManager() {}
    int num_of_scenes = 0;
    
    void update(float dt) {
        if(scenes[0].instance) scenes[0].instance->update(dt);
    }
    
    void draw() {
        if(scenes[0].instance) scenes[0].instance->draw();
    }
    
    template<typename T>
    void add(std::unique_ptr<T> scene) {
        static_assert(std::is_base_of<Scene, T>::value, "T must inherit from Scene");

        num_of_scenes++;
        scene->manager = this;

        StoredScene stored;
        stored.sceneIndex = num_of_scenes;
        scene->sceneIndex = num_of_scenes;
        stored.instance = std::move(scene);
        
        // Here it assigns the lambda function to the StoredState (it tells the recreate to be a function that does what's between {})
        stored.recreate = []() {
            return std::make_unique<T>();
        };

        scenes.push_back(std::move(stored));

        if (num_of_scenes == 1)
            scenes[0].instance->start();
    }
    
    void SwitchState(int scene_index) {
        if (!scenes[0].instance) return;

        // Refresh state[0] using its own factory
        scenes[0].instance = scenes[0].recreate();
        scenes[0].instance->manager = this;
        scenes[0].instance->sceneIndex = scenes[0].sceneIndex;

        for (int i = 0; i < scenes.size(); i++) {
            if (scenes[i].sceneIndex == scene_index) {
                std::swap(scenes[0], scenes[i]);
                break;
            }
        }

        scenes[0].instance->start();
    }
    
    void UnloadScenes() {
        // TODO: not really necessary
    }
    
    ~SceneManager() {}
};

inline void DrawLetterBox(RenderTexture2D target, float scale, float gameW, float gameH) {
    BeginDrawing();
        ClearBackground(BLACK);
        
        DrawTexturePro(target.texture, Rectangle{ 0.0f, 0.0f, (float)target.texture.width, (float)-target.texture.height },
            Rectangle{ (GetScreenWidth() - ((float)gameW*scale))*0.5f, (GetScreenHeight() - ((float)gameH*scale))*0.5f,
            (float)gameW*scale, (float)gameH*scale }, Vector2{ 0, 0 }, 0.0f, WHITE);
    EndDrawing();
}
