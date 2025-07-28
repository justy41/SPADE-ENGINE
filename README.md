# Kittylectron (formerly SPADE-ENGINE)

> A cute and chaotic game disguised as an engine.

**Kittylectron** is a small arcade-style game built in C++ with [raylib](https://www.raylib.com/) that started as a simple header-only engine experiment but evolved into a small game for my portofolio. Control a round yellow cat and leap across the screen while dodging electrifying hazards!

## Screenshots
<img src="https://github.com/justy41/SPADE-ENGINE/blob/main/screenshots/Kittylectron_00.png" width=400> <img src="https://github.com/justy41/SPADE-ENGINE/blob/main/screenshots/Kittylectron_01.png" width = 400>
<img src="https://github.com/justy41/SPADE-ENGINE/blob/main/screenshots/Kittylectron_02.png" width = 400> <img src="https://github.com/justy41/SPADE-ENGINE/blob/main/screenshots/Kittylectron_03.png" width = 400>

## Gameplay

- **Objective:** Jump from one side of the screen to the other to gain score. Reach a certain score to clear the level
- **To win:** Clear all 3 levels
- **Controls:**
  - `A`, `D` – Move the cat
  - `Space` – Jump
- **WATCH OUT FOR:**
  - Moving electricity cables coming from left and right. Please dodge them to **not** lose score!

## Project Structure

The repository includes:
- Core game logic (mostly header-based)
- Asset loading and rendering
- Simple state-based level progression
- Base -> Object -> Sprite classes
- Scene (holds Base objects)
- SceneManager (holds scenes)
- Letterbox window resolution (black bars)

- Spade-Engine:
  - [Raylib](https://www.raylib.com/) as the engines foundation
  - [LDtkLoader](https://github.com/Madour/LDtkLoader), even though it's not used in the game
  - [ImGui](https://github.com/ocornut/imgui), if I'll ever need it
  - [nlohmann's json](https://github.com/nlohmann/json)

## Status

Originally made as an engine (`SPADE-ENGINE`, name came to mind because I like playing cards), this project became a small game instead.

Future ideas:
- Add more levels and challenge variations
- Refactor engine-like features for reuse
- Add sound effects or background music
- Add a cute story

## Build Instructions

Things to have on your PC:
- A C++ compiler (I used GCC mingw32 from [w64devkit](https://github.com/skeeto/w64devkit))
- [Raylib](https://www.raylib.com/)
- [CMake](https://cmake.org/)
- A little bit of hope...

Made with love and sparks by justy41
