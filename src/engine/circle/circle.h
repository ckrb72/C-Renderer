#pragma once
#include <linmath.h>
#include "../texture/texture.h"

typedef struct circle
{
    unsigned int radius;
    vec2 pos;
    Texture* texture;
    unsigned int shader;
}circle_t;

circle_t circle_create(vec2 pos, unsigned int radius);