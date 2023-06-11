#pragma once

typedef struct
{
    unsigned int vao, vbo, ebo;

    unsigned int index_count;
}buffer_t;

buffer_t buffer_init(float* vertexBuffer, unsigned int vertexSize, unsigned int* elementBuffer, unsigned int elementSize);