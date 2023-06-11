#pragma once
#include <SDL2/SDL.h>
#include "../game_state.h"
#include "../rect/rect.h"

typedef enum render_type
{
    CG_UNKNOWN,
    CG_QUAD,
    CG_CIRCLE
}Render_Type;

//Renderable object
typedef struct renderable
{
    Render_Type type;

    //Uses union so only one of the things in the union can be used at once
    //Good if we have multiple different types (ex. quad, circle, ...)
    union
    {
        //Could also make this a pointer instead of a full copy to save space
        Render_Rect quad;

      //Render_Circle circle;
    };
}Renderable;

//Only problem is figuring out how to do all of the other functions as well

int render_init(Renderer* state, float width, float height);
void render_display(Renderer* state);
void render_clear();

void render_draw(void* data, Render_Type type);