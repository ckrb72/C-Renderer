#pragma once

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <string.h>
#else
#include <glad/glad.h>
#endif


#define SDL_MAIN_HANDELED
#include <SDL2/SDL.h>
#include "render/render.h"
#include "shader/shader.h"
#include "texture/texture.h"
#include "input/input.h"
#include "engine_state.h"

#include <linmath.h>


#define CG_TRUE 1
#define CG_FALSE 0