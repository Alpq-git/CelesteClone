#pragma once

#include "assets.h"
#include "CelesteClone_lib.h"

//############################################
//              Renderer Constant
//############################################
constexpr int MAX_TRANSFORM = 1000;

//############################################
//              Renderer Structs
//############################################
struct OrthographicCamera2D
{
    float zoom = 1.0f;
    Vec2 dimensions;
    Vec2 position;
};

struct Transform
{
    IVec2 atlasOffset;
    IVec2 spriteSize;
    Vec2 pos;
    Vec2 size;
};

struct RenderData
{
    OrthographicCamera2D gameCamera;
    OrthographicCamera2D uiCamera;

    int transformCount;
    Transform transforms[MAX_TRANSFORM];
};

//############################################
//              Renderer Globals
//############################################
static RenderData* renderData;   

//############################################
//              Renderer Untility
//############################################

//############################################
//              Renderer Functions
//############################################
void draw_sprite(SpriteID spriteID, Vec2 pos)
{
    Sprite sprite = get_sprite(spriteID);

    Transform transform = {};
    transform.pos = pos - vec_2(sprite.spriteSize) / 2.0f;
    transform.size = vec_2(sprite.spriteSize);
    transform.atlasOffset = sprite.atlasOffset;
    transform.spriteSize = sprite.spriteSize;

    renderData->transforms[renderData->transformCount++] = transform;
}