#pragma once
#include <stdint.h>

typedef struct buffer_state
{
    unsigned int vao, vbo, ebo;

    unsigned int index_size;
}Buffer_State;

typedef struct rectangle_state_internal
{
    Buffer_State rect_buffer;

    uint32_t count;

}Rectangle_State_Internal;