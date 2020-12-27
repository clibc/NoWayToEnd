#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

bool texture_generate(texture *tex, const char *file_path, texture::type type)
{
    tex->idata.data = stbi_load(file_path,
                                &tex->idata.width,
                                &tex->idata.height,
                                &tex->idata.nrChannels, 0);

    if (tex->idata.data == NULL)
        return false;

    glGenTextures(1, &tex->textureID);
    glBindTexture(GL_TEXTURE_2D, tex->textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (type == texture::PNG)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex->idata.width,
                     tex->idata.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex->idata.data);
    else if (type == texture::JPG)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex->idata.width,
                     tex->idata.height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex->idata.data);

    glGenerateMipmap(GL_TEXTURE_2D);

    return true;
}

void texture_create_sub_image(const texture &tex, int xoffset, int yoffset, int width, int height)
{
    glBindTexture(GL_TEXTURE_2D, tex.textureID);
    glTexSubImage2D(GL_TEXTURE_2D, 0, xoffset, yoffset, width, height, GL_RGBA,
                    GL_UNSIGNED_BYTE, tex.idata.data);
}
