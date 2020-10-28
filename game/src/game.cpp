#include "game.h"

Game::Game()
{
    m_renderer = ogl::renderer::GetInstance();

    m_vertices = {-1.0f, 1.0f, 0.0f, // Top-left
                  1.0f, 1.0f, 0.0f,  // Top-right
                  1.0f, -1.0f, 0.0f, // Bottom-right
                  -1.0f, -1.0f, 0.0f};

    m_shader = ogl::shader("C:/Users/root/Desktop/sdl_game/game/src/opengl/shaders/vertex.vs", "C:/Users/root/Desktop/sdl_game/game/src/opengl/shaders/fragment.vs");
    m_vb = ogl::vertexBuffer(m_vertices);
}

Game::~Game()
{
    // TODO(62bit): Destruct
}

void Game::Run()
{
    while (true)
    {
        m_renderer->Clear();
        m_renderer->Render(m_vb, m_shader);
        m_renderer->SwapBuffers();
    }
}