#pragma once
#include "../rect/rect.h"

//Might not use this function
//Have to see how I want to lay this out
void shader_init();

//Takes vertex and fragment shader as input
//Compiles the shader and returns the opengl id associated with it
unsigned int shader_compile(const char* vert, const char* frag);

void shader_set(Render_Rect* entity, unsigned int shaderProgram);

//Deletes the shader. Probably need to use this internally with a 
//Engine_Quit() function or something like that to cover clean up of all
//objects. Or maybe a free_entity() function that implicitly calls this function
//to delete the shader if it hasn't already been deleted by a different object with the same shader
void shader_delete(unsigned int shader);
