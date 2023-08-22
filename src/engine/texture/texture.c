#include "texture.h"
#include "texture_internal.h"
#include "../shader/shader.h"

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <glad/glad.h>
#endif

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "../debug.h"


//TODO: Make it so multiple textures can be used. This can be done through uniforms and binding the different textures via GL_TEXTURE0 ...

//FIXME: Doesn't work for all files so need to fix that
static Texture texture_load(const char* path, Texture_Type fileType)
{
    Texture tex;

    if(fileType != CG_JPG && fileType != CG_PNG)
        ERROR_RETURN((Texture){0}, "Invalid File Type. Texture could not be created!\n");

    //Using ternary operator here just because there are only two options at this point.
    //When I add more we can figure out an efficient way to do that but for now this is fine.
    //Could replace with normal if elseif statements but that just adds a lot of extra lines for no reason.
    unsigned int ftype = (fileType == CG_JPG) ? GL_RGB : GL_RGBA;

    //Might want to do this down the line because stbi puts [0][0] as the top left pixel instead of
    //the bottom left

    stbi_set_flip_vertically_on_load(1);

    unsigned char* data = stbi_load(path, &tex.w, &tex.h, &tex.nrChannels, 0);

    if(!data)
    {
        ERROR_RETURN((Texture){0}, "SOMETHING WENT REALLY WRONG WITH LOADING THAT TEXTURE!\n");
    }
    
    glGenTextures(1, &tex.gl_texture);
    glBindTexture(GL_TEXTURE_2D, tex.gl_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, ftype, tex.w, tex.h, 0, ftype, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    glBindTexture(GL_TEXTURE_2D, 0);

    return tex;
}

//TODO:
//Right now this is just a wrapper but will eventually make it so that a default texture shader is also
//set here and everything else that is needed as well
void texture_create(Render_Rect* entity, const char* path, Texture_Type fileType)
{
    entity->texture = texture_load(path, fileType);
    entity->shader = shader_set_texture();
}

void texture_set(Render_Rect* entity, Texture texture)
{
    entity->texture = texture;
}

void texture_delete(Texture* tex)
{
   glDeleteTextures(1, &tex->gl_texture);
   tex->h = 0;
   tex->w = 0;
   tex->nrChannels = 0;
}