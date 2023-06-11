#pragma once
#include <linmath.h>
#include "../texture/texture_internal.h"

typedef struct render_rect
{
    unsigned int width, height;

    vec2 pos;

    unsigned int shader;

    Texture texture;

    //Need to add uniforms in here somehow
}Render_Rect;
//Might want to change this to return a pointer at some point but fine for now
Render_Rect rectangle_create(vec2 position, vec2 scale);

void rectangle_set_scale(Render_Rect* quad, vec2 scale);

void rectangle_set_position(Render_Rect* quad, vec2 position);

//vec2 entity_get_scale(Entity* entity);
