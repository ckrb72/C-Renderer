#pragma once

typedef struct texture
{
    int w;
    int h;
    int nrChannels;
    unsigned int gl_texture;
}Texture;

typedef enum texture_type
{
    CG_PNG, 
    CG_JPG
}Texture_Type;
