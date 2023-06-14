#pragma once
#include <linmath.h>
#include "../texture/texture_internal.h"

typedef struct render_rect
{
    unsigned int w, h;

    vec2 pos;

    unsigned int shader;

    Texture texture;

    //Need to add uniforms in here somehow
}Render_Rect;

//Creates a quad object
//@param position: The default screen position of the quad
//@param scale: The dimensions of the quad
Render_Rect rectangle_create(vec2 position, vec2 scale);

//Sets the scale of the quad
//@param quad: Reference to the quad to be want to modify
//@param scale: The new scale you of the quad
void rectangle_set_scale(Render_Rect* quad, vec2 scale);

//Sets the position of the quad
//@param quad: Reference to the quad to be modified
//@param position: The new position of the quad
void rectangle_set_position(Render_Rect* quad, vec2 position);

//vec2 entity_get_scale(Entity* entity);
