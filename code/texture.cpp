#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

bool GenerateTexture(texture &tex)
{
    unsigned char *data = stbi_load(tex.path,
                                    &tex.idata.width,
                                    &tex.idata.height,
                                    &tex.idata.nrChannels, 0);

    if (data == NULL)
        return false;

    glGenTextures(1, &tex.textureID);
    glBindTexture(GL_TEXTURE_2D, tex.textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (tex.texType == texture::PNG)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex.idata.width,
                     tex.idata.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    else if (tex.texType == texture::JPG)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex.idata.width,
                     tex.idata.height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    return true;
}
