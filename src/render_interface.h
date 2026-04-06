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
IVec2 screen_to_world(IVec2 screenPos)
{
    OrthographicCamera2D camera = renderData->gameCamera;

    int xPos = (float)screenPos.x /
                input->screenSize.x *
                camera.dimensions.x; // [0; dimensions.x]

    //Offset using dimensions and position
    xPos += camera.dimensions.x / 2.0f + camera.position.x;

    int yPos = (float)screenPos.y /
                input->screenSize.y *
                camera.dimensions.y; // [0; dimensions.y]

    //Offset using dimension and position
    yPos += -camera.dimensions.y / 2.0f - camera.position.y;

    return {xPos, yPos};
}

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

void draw_sprite(SpriteID spriteID, IVec2 pos)
{
    draw_sprite(spriteID, vec_2(pos));
}