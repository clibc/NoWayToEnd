#pragma once
#include "opengl/gl_renderer.h"
#include "opengl/gl_shader.h"
#include "opengl/gl_vertexBuffer.h"
#include <vector>
#include "glm/glm.hpp"

class Game
{
public:
    Game();
    ~Game();
    void Run();

private:
    ogl::renderer *m_renderer;
    ogl::shader m_shader;
    ogl::vertexBuffer m_vb;
    std::vector<float> m_vertices;
};
