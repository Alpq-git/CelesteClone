#ifdef ENGİNE // Inside Game / Engine
#pragma once

#include "CelesteClone_lib.h"
#define vec2 Vec2
#define ivec2 IVec2
#define vec4 Vec4

// Inside Shader
#else

#define BIT(i) 1 << i

// Inside Both
#endif

// ###########################################################
//                      Rendiring Constants
// ###########################################################
int RENDERING_OPTION_FLIP_X = BIT(0);
int RENDERING_OPTION_FLIP_Y = BIT(1);
int RENDERING_OPTION_FONT = BIT(2);

// ###########################################################
//                      Rendiring Structs
// ###########################################################

struct Transform
{
    vec2 pos; //This is currently the top left
    vec2 size;
    iVec2 atlasOffset;
    ivec2 spriteSize;
    int renderOptions;
    float layer;
    int materialIdx; 
};

struct Material
{
    // Operator inside the Engine to compare materials
#ifdef ENGINE
    vec4 color = COLOR_WHITE;
    bool operator ==(Material other)
    {
        return color == other.color;
    }
#else
    vec4 color;
#endif
};