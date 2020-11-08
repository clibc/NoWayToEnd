#pragma once
#include "opengl/gl_renderer.h"
#include "opengl/gl_shader.h"
#include "opengl/gl_vertexBuffer.h"
#include "opengl/gl_texture.h"
#include <vector>
#include "glm/glm.hpp"
#include "level.h"

class Game
{
public:
    Game();
    ~Game();
    void RenderLevel();
    void Run();

private:
    ogl::renderer *m_renderer;
    ogl::shader m_shader;
    ogl::vertexBuffer m_vb;
    ogl::texture m_texture;
    std::vector<float> m_vertices;
    Level m_level;
};
