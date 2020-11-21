#pragma once
#include "common.h"

struct image_data
{
    // NOTE(62bit): stores data given by stb_image (stbi_load)
    int width;
    int height;
    int nrChannels;
};

struct texture
{
    // NOTE(62bit): Specify path after creating this struct
    char *path;

    image_data idata;
    unsigned int textureID;
};

bool GenerateTexture(texture &tex);
inline void BindTexture(const texture &tex) { glBindTexture(GL_TEXTURE_2D, tex.textureID); }
