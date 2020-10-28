#include "gl_renderer.h"

namespace ogl
{
    renderer *renderer::m_instance = nullptr;

    renderer::renderer(SDL_Window *window)
        : m_window(window)
    {
        if (m_instance == nullptr)
            m_instance = this;
        Init();
    }

    void renderer::Init()
    {
        // NOTE(62bit): SDL shoud already be initialized!
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        GLenum err = glewInit();
        if (err != GLEW_OK)
            DEBUG("Error: " << glewGetErrorString(err));
    }

    void renderer::RenderCube(float width, float height)
    {
        m_defShader.Bind();
    }

    void renderer::Render(ogl::vertexBuffer vb, ogl::shader shader)
    {
        shader.Bind();
        vb.Bind();
        std::cout << "this" << '\n';
        glDrawArrays(GL_QUADS, 0, vb.m_numVertices);
    }

    void renderer::Clear()
    {
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void renderer::SwapBuffers()
    {
        SDL_GL_SwapWindow(m_window);
    }
}; // namespace ogl