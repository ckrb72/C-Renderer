#pragma once

typedef struct texture
{
    int width;
    int height;
    int nrChannels;
    unsigned int gl_texture;
}Texture;

Texture texture_load(const char* path);

void texture_delete(Texture* tex);

