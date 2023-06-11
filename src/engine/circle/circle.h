#pragma once
#include <linmath.h>
#include "../texture/texture.h"
#include "circle_internal.h" 


typedef struct circle
{
    buffer_c* buffer;
    unsigned int radius;
    vec2 pos;
    Texture* texture;
    unsigned int shader;
}circle_t;

circle_t circle_create(vec2 pos, unsigned int radius);