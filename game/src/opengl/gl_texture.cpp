#include "opengl/gl_texture.h"

#define STB_IMAGE_IMPLEMENTATION

namespace ogl
{
    texture::texture(const char *texturePath, const float *coords)
        : m_textureCoords(coords)
    {
        // NOTE(62bit): setting up opengl to create texture
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        unsigned char *data = stbi_load(texturePath, &m_width,
                                        &m_height, &m_nrChannels, 0);

        glGenTextures(1, &m_texture);

        if (data)
        {
            glBindTexture(GL_TEXTURE_2D, m_texture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                         m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            DEBUG("failed to load texture");
        }

        stbi_image_free(data);
    }
};
