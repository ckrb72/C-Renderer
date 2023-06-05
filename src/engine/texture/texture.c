#include "texture.h"
#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture texture_load(const char* path, Texture_Type fileType)
{
    Texture tex;

    unsigned char* data = stbi_load(path, &tex.width, &tex.height, &tex.nrChannels, 0);

    if(data == NULL)
    {
        printf("SOMETHING WENT REALLY FUCKING WRONG!\n");
    }

    glGenTextures(1, &tex.gl_texture);
    glBindTexture(GL_TEXTURE_2D, tex.gl_texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex.width, tex.height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    glBindTexture(GL_TEXTURE_2D, 0);

    return tex;
}

void texture_delete(Texture* tex)
{
   
}