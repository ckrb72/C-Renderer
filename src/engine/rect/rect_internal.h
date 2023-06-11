#pragma once
#include <stdint.h>

typedef struct
{
    unsigned int vao, vbo, ebo;

    unsigned int index_size;
}buffer_r;

typedef struct rectangle_state_internal
{
    buffer_r rect_buffer;

    uint32_t count;

}Rectangle_State_Internal;