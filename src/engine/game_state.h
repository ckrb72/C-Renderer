#pragma once
#include <SDL2/SDL.h>
#include "render/render_internal.h"
#include "input/input_internal.h"

//The main game state struct that is going to hold all of the implemented features
typedef struct game_state
{
    Render_State render;
    Input_State input;
}Game_State;