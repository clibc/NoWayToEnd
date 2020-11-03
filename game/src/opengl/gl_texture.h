#pragma once
#include "GL/glew.h"
#include "gameDefines.h"

#include "stb_image.h"

namespace ogl
{
    class texture
    {
        public:
        texture() = default;
        texture(const char *texturePath, const float *coords);
        
        private:
        const float *m_textureCoords;
        int m_width;
        int m_height;
        int m_nrChannels;
        unsigned int m_texture;
    };
};
