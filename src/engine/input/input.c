#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdint.h>

#include "input.h"
#include "input_internal.h"

//Updates the keystate for a given key
//@param current_state: the number associated with the scancode of the key being queried (if it's greater than 0 then the key is being pressed)
//@param key_state: the state that is being mutate of the current key
static void update_key_state(uint8_t current_state, Key_State* key_state)
{

    //If the current_state is 1, that means the key is being pressed
    if(current_state)
    {
        //If the key_state > 0, that means the key was previously pressed, meaning that it is being held
        if(*key_state > 0)
        {
            *key_state = KS_HELD;
        
        //else the key is just being pressed (this usually only happens on the first frame the key is pressed, but helps for things such as toggles)
        } else
        {
            *key_state = KS_PRESSED;
        }
    
    //else the key is not being held and the key is "unpressed"
    } else
    {
        *key_state = KS_UNPRESSED;
    }
}

//Will fill this out eventually
void input_update(Renderer* state)
{

    //SDL_GetKeyboardState returns an array of integers that define all the states of each key on the keyboard
    //If the number at the index given by the scancode of a particular key is 1, then the key is being pressed
    const uint8_t* keyboard_state = SDL_GetKeyboardState(NULL);

    //Updates the keystate of a given key
    //If the keyboard_state of that scancode is 1, it sets the key_state to either pressed or held, else it sets it to unpressed
    update_key_state(keyboard_state[SDL_GetScancodeFromName("Escape")], &state->input.escape);
    update_key_state(keyboard_state[SDL_GetScancodeFromName("D")], &state->input.right);
    update_key_state(keyboard_state[SDL_GetScancodeFromName("A")], &state->input.left);
    update_key_state(keyboard_state[SDL_GetScancodeFromName("S")], &state->input.down);
    update_key_state(keyboard_state[SDL_GetScancodeFromName("w")], &state->input.up);
    update_key_state(keyboard_state[SDL_GetScancodeFromName("Space")], &state->input.space);
}