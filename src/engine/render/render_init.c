#include "render_internal.h"
#include "render.h"
#include "../debug.h"
#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <stdio.h>

SDL_Window* render_init_window(float width, float height)
{
    //Sets the opengl version
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    //Inits sdl video
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        ERROR_EXIT("Failed to load SDL: %s\n", SDL_GetError())
    }

    //Creates the SDL window
    SDL_Window* window = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);

    //Sets the opengl context to the current window
    SDL_GL_CreateContext(window);

    //Loads Glad
    if(!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        printf("Failed to load Glad\n");
    }

    return window;
}