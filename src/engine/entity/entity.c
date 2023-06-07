#include "buffer.h"
#include "entity.h"
#include "../shader/shader.h"
#include <stdio.h>

//Creates the entity with the given position
//Gives the entity the default shader
Entity entity_create(vec2 position, vec2 scale)
{
    Entity entity =
    {  
        .buffer = buffer_init(),
        .pos = {position[0], position[1]},
        .scale = {scale[0], scale[1]},
        .shader = shader_compile("./res/shaders/default.vert", "./res/shaders/default.frag")
    };

    return entity;
}

void entity_set_scale(Entity* entity, vec2 scale)
{
    entity->scale[0] = scale[0];
    entity->scale[1] = scale[1];
}

void entity_set_position(Entity* entity, vec2 position)
{
    entity->pos[0] = position[0];
    entity->pos[1] = position[1];
}

/*vec2 entity_get_scale(Entity* entity)
{
    return entity->scale;
}*/