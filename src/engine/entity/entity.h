#pragma once
#include <linmath.h>
#include "../texture/texture_internal.h"

//Would like this to be in buffer.h but whenever I put
//it there the whole thing FUCKING breaks????!!!!?!?!?
typedef struct buffer_state
{
    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;

    unsigned int index_size;
}Buffer_State;

//Proably want to make this all dynamic in some way but idk how to do that
//so this is good for now
typedef struct entity
{
    Buffer_State buffer;
    vec2 pos;
    vec2 scale;
    unsigned int shader;
    Texture texture;
}Entity;

//Might want to change this to return a pointer at some point but fine for now
Entity entity_create(vec2 position, vec2 scale);

void entity_set_scale(Entity* entity, vec2 scale);

void entity_set_position(Entity* entity, vec2 position);

//vec2 entity_get_scale(Entity* entity);