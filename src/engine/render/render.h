#pragma once
#include <SDL2/SDL.h>
#include "../engine_state.h"
#include "../rect/rect.h"

#define MAX_QUADS 10000

typedef enum render_type
{
    CG_UNKNOWN,
    CG_QUAD,
    CG_CIRCLE
}Render_Type;

//Initializes rendering functionality
//Must be called before any rendering an be done
int render_init(Renderer* state, float width, float height);

//Displays the buffer that is currently being drawed to
void render_display(Renderer* state);

//Clears the back buffer and prepares for drawing again
void render_clear();

//Takes in any entity and draws it to the buffer
//Must specify type of thing being drawn as parameter
void render_draw(void* data, Render_Type type);


/*  Not using this but this is another way to do the render_draw function
    By having a wrapper struct that has a union of every possible type we need,
    we can just convert the structs to renderables and then pass the renderables into the funcitons
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
*/