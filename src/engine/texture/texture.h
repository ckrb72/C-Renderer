#pragma once

typedef struct texture
{
    int width;
    int height;
    int nrChannels;
    unsigned int gl_texture;
}Texture;

typedef enum texture_type
{
    CG_PNG, 
    CG_JPG
}Texture_Type;

Texture texture_load(const char* path, Texture_Type fileType);

void texture_delete(Texture* tex);

