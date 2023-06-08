#include "input.h"
#include <SDL2/SDL.h>
#include <stdio.h>


void keyboard(unsigned char key, int x, int y);

void keyboard(unsigned char key, int x, int y)
{
    // if(key == INPUT_KEY_LEFT)
    
    if(key == INPUT_KEY_ESCAPE)
    {
        SDL_QUIT;
    }
}