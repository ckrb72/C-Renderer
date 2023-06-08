#pragma once

typedef enum input_key
{
    INPUT_KEY_LEFT = 'a',
    INPUT_KEY_RIGHT = 'd',
    INPUT_KEY_UP = 'w',
    INPUT_KEY_DOWN = 's',
    INPUT_KEY_ESCAPE = 27
}Input_Key;

typedef enum key_state
{
    KS_UNPRESSED,
    KS_PRESSED,
    KS_HELD
}Key_State;

typedef struct input_state
{
    Key_State left;
    Key_State right;
    Key_State up;
    Key_State down;
    Key_State escape;
}Input_State;

void input_update(void);