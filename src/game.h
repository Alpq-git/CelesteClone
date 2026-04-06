#pragma once

#include "input.h"
#include "CelesteClone_lib.h"
#include "render_interface.h"

//########################################################
//                      Game Globals
//########################################################

//########################################################
//                      Game Structs
//########################################################
enum GameInputType
{
    MOVE_LEFT,
    MOVE_RIGHT,
    MOVE_UP,
    MOVE_DOWN,
    JUMP,

    MOUSE_LEFT,
    MOUSE_RIGHT,

    GAME_INPUT_COUNT
};

struct KeyMapping
{
    Array<KeyCodeID, 3>keys;
}
struct GameState
{
    bool initialized = false;
    IVec2 playerPos;
};

//########################################################
//                      Game Globals
//########################################################
static GameState* gameState;

//########################################################
//                      Game Functions (Exposed)
//########################################################
extern "C"
{
    EXPORT_FN void update_game(GameState* gameStateIn, RenderData* renderDataIN, Input* inputIn);
}
