#pragma once
#include <glad/glad.h>
#include "rect.h"

buffer_r rect_buffer_init()
{

    //Sets basic vertex positions
    //(They get changed when the projection and model matricies are introduced in the shader)
    float vertices[] = 
    {
                            //UV coords but might want to put this in separate buffer
                            //to make it more dynamic
        -0.5, -0.5, 0.0,    0.0, 0.0,
        0.5, -0.5, 0.0,     1.0, 0.0,
        0.5, 0.5, 0.0,      1.0, 1.0,
        -0.5, 0.5, 0.0,     0.0, 1.0
    };

    //Indices of a square.
    //Not dynamic at the moment and will probably have to change this so 
    //that it can handle any number of indicies later down the line
    unsigned int indices[] = 
    {
        0, 1, 2,
        2, 3, 0
    };



    buffer_r buffer;

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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //Just so it's clear what's going on, the last argument is a void pointer that holds the address of the offset, so in this case the pointer would
    //be the address 24 because 3 * 8 is 24. NOTE: It is the address that is 24, not the value of the pointer
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //Unbinds the VAO so nothing accidentally changes it
    glBindVertexArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //Records the size of the index buffer
    buffer.index_size = sizeof(indices);

    return buffer;    
}