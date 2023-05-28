#pragma once
#include <SDL2/SDL.h>

//Holds the window
typedef struct render_state
{
    SDL_Window* window;
    float width;
    float height;
}Render_State;

SDL_Window* render_init_window(float width, float height);