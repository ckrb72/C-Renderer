#pragma once
#include "../rect/rect.h"

/*
    Might want to do something like this that automatically assigns the texture without having to access the
    struct directly as that is bad practice I guess.

    void texture_create(Entity* entity, const char* path, Texture_Type fileType);

    And then inside the texture_create funciton texture_load is called. Would need to make texture_load static so that
    people don't accidentally call that instead of texture_create();
*/

//Loads a texture and binds it to the given entity
//@param entity: The entity the texture will be bound to
//@param path: The filepath of the texture to be loaded
//@param fileType: The type of file to be loaded (ex. CG_PNG, CG_JPG)
void texture_create(Render_Rect* entity, const char* path, Texture_Type fileType);

//Binds the given texture to the given entity
//@param entity: The entity the texture will be bound to
//@param texture: The texture to be bound
void texture_set(Render_Rect* entity, Texture texture);


//Deletes the given texture
//@param tex: A reference to the texture to be deleted
void texture_delete(Texture* tex);

