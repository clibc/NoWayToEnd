#include "game.h"

Game::Game()
{
    m_renderer = ogl::renderer::GetInstance();
    m_renderer->SetViewPort(WIN_W, WIN_H);

    m_level = Level("../levels/level1.lvl");

    static GLfloat vertices[] = {
        // positions      // texture coords
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f   // top left
    };

    m_shader = ogl::shader("../src/opengl/shaders/vertex.vs",
                           "../src/opengl/shaders/fragment.vs");

    m_vb = ogl::vertexBuffer(&vertices[0], sizeof(vertices));
    m_vb.SetVertexAttribArray(0, 3, 5 * sizeof(GLfloat), 0);
    m_vb.SetVertexAttribArray(1, 2, 5 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));

    glm::mat4 model = glm::translate(glm::mat4(1.0f),
                                     glm::vec3(50.0f,
                                               50.0f, 0.0f));
    model = glm::scale(model, glm::vec3(CELLSIZE, CELLSIZE, 0));

    m_shader.SetUniform3fv("color", glm::vec3(1.0f, 0.0f, 0.0f));
    m_shader.SetUniformMat4f("mvp", m_renderer->m_mvp);
    m_shader.SetUniformMat4f("model", model);

    static float tempCoords[] = {
        1.0f, 1.0f};
    m_texture = ogl::texture("wall.png",
                             &tempCoords[0]);
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
        m_renderer->Clear();
        RenderLevel();
        m_renderer->SwapBuffers();
    }
}

void Game::RenderLevel()
{
    // TODO(62bit): Draw these in the right order
    for (int i = 0; i < m_level._blocks.size(); ++i)
    {
        switch (m_level._blocks[i])
        {
        case Wall:
        {
            glm::vec2 pos;
            float row = i / COLUMNCOUNT;
            float column = i % ROWCOUNT;
            ConvertToPos(&pos, row, column);
            RenderCubeAtPosition(pos.x, pos.y);
        }
        break;
        case Empty:
            break;
        case Gate:
            break;
        case PlayerLoc:
            break;
        default:
            break;
        }
    }
}

void Game::RenderCubeAtPosition(float x, float y)
{
    glm::mat4 model = glm::translate(glm::mat4(1.0f),
                                     glm::vec3(x, y, 0.0f));
    model = glm::scale(model, glm::vec3(CELLSIZE, CELLSIZE, 0));

    m_shader.SetUniformMat4f("model", model);
    m_renderer->RenderQuad(m_vb, m_shader);
}
