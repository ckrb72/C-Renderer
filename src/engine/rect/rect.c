#include "rect_buffer.h"
#include "rect.h"
#include "../shader/shader.h"
#include <stdio.h>

static Rectangle_State_Internal rectangle_internal = {0};

static void rectangle_state_init()
{
    rectangle_internal.rect_buffer = buffer_init();
}

//Creates the entity with the given position
//Gives the entity the default shader
Render_Rect rectangle_create(vec2 position, vec2 scale)
{

    if(rectangle_internal.count == 0)
        rectangle_state_init();

    Render_Rect quad =
    {  
        .buffer = &rectangle_internal.rect_buffer,
        .width = scale[0],
        .height = scale[1],
        .pos = {position[0], position[1]},

        //Need to figure out how to reuse shaders that need to be reused
        //For example if two squares have the same shader, then we don't want to recompile them and waste space so we should figure out a way to reuse them
        .shader = shader_set_default(),
        .texture = 0
    };

    rectangle_internal.count++;

    return quad;
}

void rectangle_set_scale(Render_Rect* quad, vec2 scale)
{
    quad->width = scale[0];
    quad->height = scale[1];
}

void rectangle_set_position(Render_Rect* quad, vec2 position)
{
    quad->pos[0] = position[0];
    quad->pos[1] = position[1];
}

/*vec2 entity_get_scale(Entity* entity)
{
    return entity->scale;
}*/