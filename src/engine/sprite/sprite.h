#pragma once

typedef struct sprite
{
    unsigned int texture;
    unsigned int width;
    unsigned int height;
}Sprite;

//Might want to change this to return a pointer instead but fine for now
Sprite load_texture(const char* path);

void delete_texture(unsigned int texture);

int free_sprite(Sprite* sprite);