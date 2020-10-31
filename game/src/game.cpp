#include "game.h"

Game::Game()
{
    m_renderer = ogl::renderer::GetInstance();
    m_renderer->SetViewPort(WIN_W, WIN_H);

    static GLfloat g_vertex_buffer_data[] = {
        -0.5f, 0.5f, 0.0f, // Top-left
        0.5f, 0.5f, 0.0f,  // Top-right
        0.5f, -0.5f, 0.0f, // Bottom-right
        -0.5f, -0.5f, 0.0f};

    for (int i = 0; i < sizeof(g_vertex_buffer_data); ++i)
    {
        m_vertices.push_back(g_vertex_buffer_data[i]);
    }

    m_shader = ogl::shader("C:/Users/root/Desktop/sdl_game/game/src/opengl/shaders/vertex.vs",
                           "C:/Users/root/Desktop/sdl_game/game/src/opengl/shaders/fragment.vs");
    m_vb = ogl::vertexBuffer(m_vertices);
    m_vb.SetVertexAttribArray(0, 3, 0, 0);

    m_shader.SetUniform3fv("color", glm::vec3(1.0f, 0.0f, 0.0f));
}

Game::~Game()
{
    // TODO(62bit): Destructor
}

void Game::Run()
{
    while (true)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
            case SDL_KEYDOWN:
                if (e.key.keysym.sym == SDLK_a)
                {
                    std::cout << "A pressed" << '\n';
                }
                else if (e.key.keysym.sym == SDLK_ESCAPE)
                {
                    std::cout << "Window Exited with key ESCAPE" << '\n';
                    return;
                }
                break;

            case SDL_WINDOWEVENT:
                if (e.window.event == SDL_WINDOWEVENT_CLOSE)
                {
                    std::cout << "Window exit" << '\n';
                    return;
                }
                break;

            default:
                break;
            }
        }

        //test
        m_renderer->Clear();
        m_renderer->RenderQuad(m_vb, m_shader);
        m_renderer->SwapBuffers();
    }
}
