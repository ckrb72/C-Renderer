#include "circle.h"
#include "../shader/shader.h"

circle_t circle_create(vec2 pos, unsigned int radius)
{
    circle_t circle = 
    {
        .pos[0] = pos[0],
        .pos[1] = pos[1],
        .shader = shader_set_default(),
        .texture = 0
    };
}