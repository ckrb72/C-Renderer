#include "texture.h"
#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "../debug.h"

Texture texture_load(const char* path, Texture_Type fileType)
{
    Texture tex;

    if(fileType != CG_JPG && fileType != CG_PNG)
        ERROR_RETURN((Texture){0}, "Invalid File Type. Texture could not be created!\n");

    //Using ternary operator here just because there are only two options at this point.
    //When I add more we can figure out an efficient way to do that but for now this is fine.
    //Could replace with normal if elseif statements but that just adds a lot of extra lines for no reason.
    unsigned int ftype = (fileType == CG_JPG) ? GL_RGB : GL_RGBA;

    unsigned char* data = stbi_load(path, &tex.width, &tex.height, &tex.nrChannels, 0);

    if(!data)
    {
        ERROR_RETURN((Texture){0}, "SOMETHING WENT REALLY FUCKING WRONG WITH LOADING THAT TEXTURE!\n");
    }

    glGenTextures(1, &tex.gl_texture);
    glBindTexture(GL_TEXTURE_2D, tex.gl_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, ftype, tex.width, tex.height, 0, ftype, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    glBindTexture(GL_TEXTURE_2D, 0);

    return tex;
}

void texture_delete(Texture* tex)
{
   
}