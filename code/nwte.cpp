#include "common.h"
#include "level_loader.h"
#include "renderer.h"
#include "shader.h"
#include "texture.h"
#include "vertexBuffer.h"
#include "window.h"

#include "stb_image.h"

void handle_input();

int main(int argc, char *args[])
{
    windowgl_sdl window = {0};
    window.name = "NoWayToEnd";
    window.width = WINDOW_WIDTH;
    window.height = WINDOW_HEIGHT;

    create_window(window);

    // NOTE(62bit): Shader
    shader mShader = {0};
    create_shader(mShader, "../code/shaders/vertex.vs",
                  "../code/shaders/fragment.vs");
    glm::mat4 projection = glm::ortho(0.0f, (float)WINDOW_WIDTH,
                                      (float)WINDOW_HEIGHT, 0.0f, -1.0f, 1.0f);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(400.0f, 400.0f, 0.0f));
    model = glm::scale(model, glm::vec3(300.0f, 300.0f, 0.0f));
    set_uniform_mat4(mShader, "model", model);
    set_uniform_mat4(mShader, "projection", projection);

    float vertices[] = {
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f};

    vertex_buffer vb;
    vb.vertices = &vertices[0];
    vb.size = sizeof(vertices);
    generate_vertex_buffer(vb);
    set_vertex_attributef(vb, 0, 3, 5 * sizeof(float), (void *)0);
    set_vertex_attributef(vb, 1, 2, 5 * sizeof(float), (void *)(3 * sizeof(float)));

    int width, height, nr;
    unsigned char *data = stbi_load("../assets/wall.png", &width, &height, &nr, 0);

    const int x = 32;
    const int y = 32;

    unsigned char clipped[(x * y) * 4];

    memcpy(clipped, data, (x * y) * 4);

    unsigned int ctexture;
    glGenTextures(1, &ctexture);
    glBindTexture(GL_TEXTURE_2D, ctexture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, clipped);

    while (true)
    {
        fill_screen_with_color(0, 0, 0, 255);
        render(mShader, vb);
        swap(window.window);
        handle_input();
    }
    return 0;
}

void handle_input()
{
    SDL_Event e;
    while (SDL_WaitEvent(&e))
    {
        switch (e.type)
        {
        case SDL_WINDOWEVENT:
            if (e.window.event == SDL_WINDOWEVENT_CLOSE)
                exit(0);
        case SDL_KEYDOWN:
            if (e.key.keysym.sym == SDLK_ESCAPE)
                exit(0);
            else if (e.key.keysym.sym == SDLK_c)
                set_rendering_mode(WIREFRAME);
        default:
            break;
        }
    }
}
