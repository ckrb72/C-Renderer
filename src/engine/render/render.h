#pragma once
#include <SDL2/SDL.h>
#include "../game_state.h"
#include "../rect/rect.h"

//Can either use function pointers and enum with void* to allow for drawing anything

//Or do the following with enums and unions

//Defines the types available
typedef enum
{
    RENDER_TYPE_UNKOWN,
    RENDER_RECT
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

//TODO: Need to update this to use Renderable* instead of Render_Rect*
void render_draw(Render_Rect* entity);