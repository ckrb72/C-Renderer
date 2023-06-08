#pragma once
#include "../rect/rect.h"

/*
    Might want to do something like this that automatically assigns the texture without having to access the
    struct directly as that is bad practice I guess.

    void texture_create(Entity* entity, const char* path, Texture_Type fileType);

    And then inside the texture_create funciton texture_load is called. Would need to make texture_load static so that
    people don't accidentally call that instead of texture_create();
*/

void texture_create(Render_Rect* entity, const char* path, Texture_Type fileType);

void texture_set(Render_Rect* entity, Texture texture);

void texture_delete(Texture* tex);

