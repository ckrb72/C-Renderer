#include "buffer.h"
#include "entity.h"
#include "../shader/shader.h"
#include <stdio.h>

Entity create_entity(vec2 position)
{
    Entity entity =
    {  
        .buffer = buffer_init(),
        .pos = {position[0], position[1]},
        .shader = shader_compile("./res/shaders/default.vert", "./res/shaders/default.frag")
    };

    return entity;
}