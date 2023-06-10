#include "shader.h"
#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>
#include "../debug.h"

static Shaders shaders = {0};

void shader_init()
{
    shaders.regular = shader_compile("./res/shaders/default.vert", "./res/shaders/default.frag");
    shaders.texture = shader_compile("./res/shaders/texture.vert", "./res/shaders/texture.frag");
}

//Fix this to use new format
static char* load_shader(const char* path)
{
    //Holds the data
    char* buffer = 0;
    long length = 0;
    char current_char;
    
    //Opens file stream
    FILE* source = fopen(path, "r");
    if(!source)
        ERROR_RETURN(NULL, "Failed to load source: %s\n", path);
    
    //Goes through each character to see how long the file is
    while(current_char != EOF)
    {
        current_char = fgetc(source);
        if(current_char != EOF)
            length++;
    }

    //Rewinds back to start of file
    rewind(source);

    //Allocates appropriate space
    buffer = (char*)malloc(length + 1);

    //Puts chars in buffer
    for(int i = 0; i < length; i++)
    {
        current_char = fgetc(source);
        buffer[i] = current_char;
    }

    //Makes sure there is a null terminator
    buffer[length] = '\0';

    //Closes file
    fclose(source);

    //Returns the string
    return buffer;
}

unsigned int shader_compile(const char* vert, const char* frag)
{

    int success;
    char log[512];

    //Parse shader into string
    char* vert_source = load_shader(vert);

    const char* vertex_source = vert_source;
    //Compile shader
    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_source, NULL);
    glCompileShader(vertex_shader);
    //printf("Compiled vertex shader\n");

    //Should add error checking
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertex_shader, 512, NULL, log);
        ERROR_EXIT("Error compiling vertex shader. %s\n", log);
    }

    //Parse other shader into string
    char* frag_source = load_shader(frag);
    const char* fragment_source = frag_source;

    //Compile other shader
    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_source, NULL);
    glCompileShader(fragment_shader);
    //printf("Compiled fragment shader\n");
    
    //Should add error checking
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragment_shader, 512, NULL, log);
        ERROR_EXIT("Error compiling fragment shader. %s\n", log);
    }


    //Link shader
    unsigned int program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    //printf("Linked Program\n");

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(program, 512, NULL, log);
        ERROR_EXIT("Error linking shader. %s\n", log);
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    free(vert_source);
    free(frag_source);

    vert_source = NULL;
    frag_source = NULL;

    //return shader
    return program;
}

unsigned int shader_set_default()
{
    return shaders.regular;
}

unsigned int shader_set_texture()
{
    return shaders.texture;
}

void shader_set(Render_Rect* entity, unsigned int shaderProgram)
{
    entity->shader = shaderProgram;
}

void shader_delete(unsigned int shader)
{
    glDeleteProgram(shader);
}

void shader_setUniform1i(unsigned int shader, const char* name, int value)
{
    glUniform1i(glGetUniformLocation(shader, name), value);
}

void shader_setMat4fv(unsigned int shader, const char* name, mat4x4 value)
{
    glUniformMatrix4fv(glGetUniformLocation(shader, name), 1, GL_FALSE, &value[0][0]);
}