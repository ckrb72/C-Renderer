#pragma once
#include <SDL2/SDL.h>
#include <linmath.h>

//Holds the window
typedef struct render_state
{
    SDL_Window* window;
    float width;
    float height;

    mat4x4 projection;
}Render_State;

//Initializes the window and creates a valid OpenGL context via SDL
SDL_Window* render_init_window(float width, float height);