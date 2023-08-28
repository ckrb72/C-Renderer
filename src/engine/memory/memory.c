#include "memory.h"

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <glad/glad.h>
#endif

static int e_count = 0;


void memory_init()
{
    e_count = 0;
}

void memory_add(void* data)
{


    //If everything goes well update entity count
    e_count++;
}