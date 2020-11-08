#pragma once
#include "GL/glew.h"
#include "SDL.h"
#include "gameDefines.h"
#include "glm/glm.hpp"
#include "opengl/gl_shader.h"
#include "opengl/gl_vertexBuffer.h"
#include <iostream>

namespace ogl
{
    class renderer
    {
    public:
        renderer() = default;
        renderer(SDL_Window *window);
        static inline renderer *GetInstance() { return m_instance; }
        void Render();
        void RenderQuad(ogl::vertexBuffer &vb, ogl::shader &shader);
        void RenderTriangle(ogl::vertexBuffer &vb, ogl::shader &shader);
        void SetViewPort(int x, int y);
        void Clear();
        void SwapBuffers();

    private:
        void Init();
        SDL_Window *m_window;
        static renderer *m_instance;
        shader m_defShader;
        glm::mat4 m_ortho;
        glm::mat4 m_view;

    public:
        glm::mat4 m_mvp;
    };

}; // namespace ogl
