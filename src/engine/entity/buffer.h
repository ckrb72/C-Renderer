#pragma once
#include <glad/glad.h>
#include "entity.h"

Buffer_State buffer_init()
{

    //Sets basic vertex positions
    //(They get changed when the projection and model matricies are introduced in the shader)
    float vertices[] = 
    {
        -0.5, -0.5, 0.0,
        0.5, -0.5, 0.0,
        0.5, 0.5, 0.0,
        -0.5, 0.5, 0.0
    };

    //Indices of a square.
    //Not dynamic at the moment and will probably have to change this so 
    //that it can handle any number of indicies later down the line
    unsigned int indices[] = 
    {
        0, 1, 2,
        2, 3, 0
    };


    Buffer_State buffer;

    //Generates the VAO, VBO, and EBO
    glGenVertexArrays(1, &buffer.vao);
    glGenBuffers(1, &buffer.vbo);
    glGenBuffers(1, &buffer.ebo);

    //Binds the VAO so the VBO and EBO get saved in it
    glBindVertexArray(buffer.vao);
    
    //Binds the VAO and sets the buffer data
    glBindBuffer(GL_ARRAY_BUFFER, buffer.vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //Binds the EBO and sets the buffer data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer.ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //Sets the Vertex Pointer
    //Just uses one because it's only 3 vertices and no UV's at this point
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //Unbinds the VAO so nothing accidentally changes it
    glBindVertexArray(0);

    //Records the size of the index buffer
    buffer.index_size = sizeof(indices);

    return buffer;    
}