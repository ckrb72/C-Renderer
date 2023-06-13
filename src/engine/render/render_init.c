#include "render_internal.h"
#include "render.h"
#include "../debug.h"

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <string.h>
#else
#include <glad/glad.h>
#endif

#include <SDL2/SDL.h>
#include <stdio.h>

SDL_Window* render_init_window(float width, float height)
{

    //Creates the SDL window
    SDL_Window* window = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);

    //Inits sdl video
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        #ifndef __APPLE__
        ERROR_EXIT("Failed to load SDL: %s\n", SDL_GetError())
        #endif
    }

    //Sets the opengl version
    #ifndef __APPLE__
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    #else
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    #endif


    //Sets the opengl context to the current window
    SDL_GL_CreateContext(window);

    #ifdef __APPLE__
    printf("GL Version: %s\n", glGetString(GL_VERSION));
    printf("GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    #endif

    #ifndef __APPLE__
    //Loads Glad
    if(!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        printf("Failed to load Glad\n");
    }
    #endif

    return window;
}