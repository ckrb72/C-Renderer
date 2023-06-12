/*
    - ALl structs for input are define in input_internal.h to prevent cyclic dependencies in header files
*/

#pragma once
#include "../engine_state.h"

//Updates the input state to reflect what is currently being pressed on the keyboard
void input_update(Renderer* state);