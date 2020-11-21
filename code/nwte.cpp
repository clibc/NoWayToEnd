#include "GL/glew.h"
#include "SDL.h"
#include "common.h"
#include "renderer.h"
#include "shader.h"
#include "glm/glm.hpp"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main(int argc, char *args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("nwte",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          WINDOW_WIDTH,
                                          WINDOW_HEIGHT,
                                          SDL_WINDOW_OPENGL);
    SDL_GL_CreateContext(window);

    SetAttribs();

    GLenum error = glewInit();
    if (error != GLEW_OK)
    {
        printf("%s", glewGetErrorString(error));
        return 1;
    }

    float vertices[] = {
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f};

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    shader mShader = CreateShader("../code/shaders/vertex.vs",
                                  "../code/shaders/fragment.vs");

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // NOTE(62bit): Texture
    int width, height, nrChannels;
    unsigned char *data = stbi_load("../assets/texture.jpg",
                                    &width, &height, &nrChannels, 0);

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,
                 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
    // Texture

    {
        int atrribcount;
        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &atrribcount);
        debug("Max Number of Attributes supported : " << atrribcount);
    }

    // NOTE(62bit): projection stuff

    glm::mat4 projection = glm::ortho(0.0f, (float)WINDOW_WIDTH,
                                      (float)WINDOW_HEIGHT, 0.0f,
                                      -1.0f, 1.0f);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(300.0f, 300.0f, 0.0f));
    model = glm::scale(model, glm::vec3(590.0f, 590.0f, 0.0f));

    debug(SetUniformMat4(mShader, "model", model));
    debug(SetUniformMat4(mShader, "projection", projection));

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

            FillScreenWithColor(window, 0, 0, 0, 255);
            Render(mShader, VBO);
            Swap(window);
        }
    }

    return 0;
}
