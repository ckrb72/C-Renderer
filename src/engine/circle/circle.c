#include "circle.h"
#include "../shader/shader.h"

static buffer_c circle_buffer;
static unsigned int circle_count = 0;


//Figure out how to create circle
static buffer_c circle_buffer_init()
{
    return (buffer_c){0};
}

circle_t circle_create(vec2 pos, unsigned int radius)
{
    if(circle_count == 0)
        circle_buffer_init();

    circle_t circle = 
    {
        .buffer = &circle_buffer,
        .pos[0] = pos[0],
        .pos[1] = pos[1],
        .shader = shader_set_default(),
        .texture = 0
    };

    circle_count++;
}