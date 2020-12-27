#include "common.h"
#include "level_loader.h"
#include "renderer.h"
#include "shader.h"
#include "texture.h"
#include "vertexBuffer.h"
#include "window.h"
#include "animation.h"
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

    //NOTE(62bit): This crap is not here for a reason. It is because of me being an idiot
    glm::vec3 vertxPos1(0.5f, 0.5f, 0.0f);
    glm::vec3 vertxPos2(0.5f, -0.5f, 0.0f);
    glm::vec3 vertxPos3(-0.5f, -0.5f, 0.0f);
    glm::vec3 vertxPos4(-0.5f, 0.5f, 0.0f);

    set_uniform_vec3(mShader, "c_positions[0]", vertxPos1);
    set_uniform_vec3(mShader, "c_positions[1]", vertxPos2);
    set_uniform_vec3(mShader, "c_positions[2]", vertxPos3);
    set_uniform_vec3(mShader, "c_positions[3]", vertxPos4);

    set_uniform_mat4(mShader, "model", model);
    set_uniform_mat4(mShader, "projection", projection);

    float vertices[] = {
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f};
    vertex_buffer vb;
    vb.vertices = &vertices[0];
    vb.size = sizeof(vertices);
    generate_vertex_buffer(vb);
    set_vertex_attributef(vb, 0, 3, 3 * sizeof(float), (void *)0);

    texture tex;
    texture_generate(&tex, "../assets/coin.png", texture::PNG);

    //32
    const int sprite_size = 32;
    float x = (float)sprite_size / (float)tex.idata.width;
    int i = 0;
    glm::vec2 texPos1(x + (x * float(i)), 1.0f);
    glm::vec2 texPos2(x + (x * float(i)), 0.0f);
    glm::vec2 texPos3(x * i, 0.0f);
    glm::vec2 texPos4(x * i, 1.0f);

    animation coin_animation;
    create_animation(&coin_animation, &tex, 32);

    set_uniform_vec2(mShader, "t_positions[0]", texPos1);
    set_uniform_vec2(mShader, "t_positions[1]", texPos2);
    set_uniform_vec2(mShader, "t_positions[2]", texPos3);
    set_uniform_vec2(mShader, "t_positions[3]", texPos4);

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
