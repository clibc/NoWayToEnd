#define STB_IMAGE_IMPLEMENTATION

#include "opengl/gl_texture.h"

namespace ogl
{
    texture::texture(const char *texturePath, const float *coords)
        : m_textureCoords(coords)
    {
        
        // NOTE(62bit): setting up opengl to create texture
        
        glGenTextures(1, &m_texture);
        glBindTexture(GL_TEXTURE_2D, m_texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        unsigned char *data = stbi_load(texturePath, &m_width,
                                        &m_height, &m_nrChannels, STBI_rgb);
        
        if (data)
        {
            // NOTE(62bit): Specify 'GL_RGB' if you load .jpg file
            // 'GL_RGBA' for .png file 
            // Access violation occurs if you don't specify it correctly
            
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                         m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            DEBUG("failed to load texture");
        }
        
        stbi_image_free(data);
        
    }
};
