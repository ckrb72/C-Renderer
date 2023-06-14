#pragma once
//this will have all of the ecs and memory management stuff

//Max entites per draw call
#define MAX_ENTITIES 10000

//Initializes memory state of engine
void memory_init();

//Adds given entity to buffer to be sent to graphics card
//@param data: void* to entity being added to buffer.
//Might want to change this up a bit and have it pass in the vertices and uv's created from the size and shape of the quad
void memory_add(void* data);

//Alternate function prototype that passes in a pointer to the vertex and uv coords which could be calculated in the individual draw functions
//void memory_add(float* vertex_buffer)