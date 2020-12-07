#pragma once
#include "common.h"

struct image_data
{
    // NOTE(62bit): stores data given by stb_image (stbi_load)
    int width;
    int height;
    int nrChannels;

    unsigned char *data;
};

struct texture
{
    enum type
    {
        JPG,
        PNG
    };
    // NOTE(62bit): Specify path after creating this struct
    char *path;
    type texType;

    image_data idata;
    unsigned int textureID;
};

bool texture_generate(texture &tex);
inline void texture_bind(const texture &tex) { glBindTexture(GL_TEXTURE_2D, tex.textureID); }
void texture_create_sub_image(const texture &tex, int xoffset, int yoffset, int width, int height);
