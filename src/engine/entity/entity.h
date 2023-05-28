#pragma once
#include <linmath.h>

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
    unsigned int shader;
}Entity;

//Might want to change this to return a pointer at some point but fine for now
Entity create_entity(vec2 position);