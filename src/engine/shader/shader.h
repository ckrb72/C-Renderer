#pragma once
#include "../rect/rect.h"

typedef struct shaders
{
    unsigned int regular;
    unsigned int texture;
}Shaders;

//Might not use this function
//Have to see how I want to lay this out
void shader_init();

//Takes vertex and fragment shader as input
//Compiles the shader and returns the opengl id associated with it
//@param vert: The path to the vertex shader
//@param frag: The path to the fragment shader
unsigned int shader_compile(const char* vert, const char* frag);

//Sets the shader of a given entity to the given shader
//@param entity: The entity to be modified
//@param shaderProgram: gl ID of the shader you want to set
void shader_set(Render_Rect* entity, unsigned int shaderProgram);

//Deletes the shader. Probably need to use this internally with a 
//Engine_Quit() function or something like that to cover clean up of all
//objects. Or maybe a free_entity() function that implicitly calls this function
//to delete the shader if it hasn't already been deleted by a different object with the same shader
void shader_delete(unsigned int shader);


void shader_setUniform1i(unsigned int shader, const char* name, int value);
void shader_setMat4fv(unsigned int shader, const char* name, mat4x4 value);

//Will definitely want to figure out a better way to do this in the future but for now this works

//Gets the shader ID of the default shader and returns it
unsigned int shader_set_default();

//Gets the shader ID of the texture shader and returns it
unsigned int shader_set_texture();