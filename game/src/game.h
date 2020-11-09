#pragma once
#include "glm/glm.hpp"
#include "level.h"
#include "opengl/gl_renderer.h"
#include "opengl/gl_shader.h"
#include "opengl/gl_texture.h"
#include "opengl/gl_vertexBuffer.h"
#include "utils.h"
#include <vector>

class Game
{
public:
    Game();
    ~Game();
    void RenderLevel();
    void RenderCubeAtPosition(float x, float y);
    void Run();

private:
    ogl::renderer *m_renderer;
    ogl::shader m_shader;
    ogl::vertexBuffer m_vb;
    ogl::texture m_texture;
    std::vector<float> m_vertices;
    Level m_level;
};
