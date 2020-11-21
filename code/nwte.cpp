#include "window.h"
#include "common.h"
#include "renderer.h"
#include "shader.h"
#include "vertexBuffer.h"
#include "texture.h"
#include "glm/glm.hpp"
#include <iostream>

int main(int argc, char *args[])
{
    windowgl_sdl window;
    window.name = "NoWayToEnd";
    window.width = WINDOW_WIDTH;
    window.height = WINDOW_HEIGHT;

    CreateWindow(window);

    // NOTE(62bit): Shader
    shader mShader = CreateShader("../code/shaders/vertex.vs",
                                  "../code/shaders/fragment.vs");
    glm::mat4 projection = glm::ortho(0.0f, (float)WINDOW_WIDTH,
                                      (float)WINDOW_HEIGHT, 0.0f,
                                      -1.0f, 1.0f);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(300.0f, 300.0f, 0.0f));
    model = glm::scale(model, glm::vec3(590.0f, 590.0f, 0.0f));
    debug(SetUniformMat4(mShader, "model", model));
    debug(SetUniformMat4(mShader, "projection", projection));
    //

    // NOTE(62bit): VertexBuffer
    float vertices[] = {
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f};

    vertex_buffer vb;
    vb.vertices = &vertices[0];
    vb.size = sizeof(vertices);
    GenerateVertexBuffer(vb);
    SetAttributeF(vb, 0, 3, 5 * sizeof(float), (void *)0);
    SetAttributeF(vb, 1, 2, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    //

    // NOTE(62bit): Texture
    texture tex;
    tex.path = "../assets/texture.jpg";
    GenerateTexture(tex);
    BindTexture(tex);
    //
    {
        int atrribcount;
        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &atrribcount);
        debug("Max Number of Attributes supported : " << atrribcount);
    }

    while (true)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
            case SDL_WINDOWEVENT:
                if (e.window.event == SDL_WINDOWEVENT_CLOSE)
                    return 0;
            case SDL_KEYDOWN:
                if (e.key.keysym.sym == SDLK_ESCAPE)
                    return 0;
                else if (e.key.keysym.sym == SDLK_c)
                    SetRenderingMode(WIREFRAME);
            default:
                break;
            }

            FillScreenWithColor(0, 0, 0, 255);
            Render(mShader, vb);
            Swap(window.window);
        }
    }

    return 0;
}
