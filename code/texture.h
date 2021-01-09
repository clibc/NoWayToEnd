#pragma once
#include "common.h"

// NOTE(62bit): stores data given by stb_image ( stbi_load() )
struct image_data
{
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

    image_data idata;
    unsigned int textureID;
};

bool texture_generate(texture *tex, const char *file_path, texture::type type);
inline void texture_bind(const texture &tex) { glBindTexture(GL_TEXTURE_2D, tex.textureID); }
void texture_create_sub_image(const texture &tex, int xoffset, int yoffset, int width, int height);