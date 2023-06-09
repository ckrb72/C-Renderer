#pragma once
#include <SDL2/SDL.h>

//Not currently used
typedef enum input_key
{
    INPUT_KEY_LEFT,
    INPUT_KEY_RIGHT,
    INPUT_KEY_UP,
    INPUT_KEY_DOWN,
    INPUT_KEY_ESCAPE
}Input_Key;

//Defines what state a particular key is in
typedef enum key_state
{
    KS_UNPRESSED,
    KS_PRESSED,
    KS_HELD
}Key_State;

//A list of all possible valid input keys
typedef struct input_state
{
    Key_State left;
    Key_State right;
    Key_State up;
    Key_State down;
    Key_State escape;
    Key_State space;
}Input_State;