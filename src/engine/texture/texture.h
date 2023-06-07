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

/*
    Might want to do something like this that automatically assigns the texture without having to access the
    struct directly as that is bad practice I guess.

    void texture_create(Entity* entity, const char* path, Texture_Type fileType);

    And then inside the texture_create funciton texture_load is called. Would need to make texture_load static so that
    people don't accidentally call that instead of texture_create();
*/

void texture_delete(Texture* tex);

