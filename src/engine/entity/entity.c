#include "buffer.h"
#include "entity.h"
#include "../shader/shader.h"
#include <stdio.h>

//Creates the entity with the given position
//Gives the entity the default shader
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