#include "animation.h"
#include "common.h"
#include "level_loader.h"
#include "player.h"
#include "renderer.h"
#include "scene.h"
#include "shader.h"
#include "stb_image.h"
#include "texture.h"
#include "vertexBuffer.h"
#include "window.h"

static unsigned int lastTime = 0, currentTime;
static float deltaTime;
void handle_input();
float get_delta_time() { return deltaTime; }

const uint8_t *KeyboardStates;
inline bool get_key_down(SDL_Scancode s) { return KeyboardStates[s]; }
static scene scn;

void update_delta_time()
{
    currentTime = SDL_GetTicks();
    deltaTime = ((float)currentTime - (float)lastTime) / 1000.0f;
    lastTime = currentTime;
}

int main(int argc, char *args[])
{
    windowgl_sdl window = {0};
    create_window(window, "NoWaToEnd", WINDOW_WIDTH, WINDOW_HEIGHT);

    scene scn;
    scene_init(scn);

    batch batch_tex;
    CreateSeriesBatchTwoTextures(batch_tex, 25, 5);

    shader simpleShader;
    create_shader(simpleShader, "../code/shaders/simplebatch.vs", "../code/shaders/simplefrag.vs");
    auto modelbatch = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    modelbatch = glm::scale(modelbatch, glm::vec3(80.0f));

    set_uniform_mat4(simpleShader, "projection", scn.projection);
    set_uniform_mat4(simpleShader, "model", modelbatch);

    texture wallTex;
    texture_generate(&wallTex, "../assets/wall.png", texture::PNG);
    texture ghostTex;
    texture_generate(&ghostTex, "../assets/ghost.jpg", texture::JPG);

    texture sqareTex;
    texture_generate(&sqareTex, "../assets/square.jpg", texture::JPG);

    int samplers[2] = {0, 1};
    auto location = glGetUniformLocation(simpleShader.programID, "textures");
    glUniform1iv(location, 2, samplers);
    glBindTextureUnit(0, sqareTex.textureID);
    glBindTextureUnit(1, ghostTex.textureID);

    texture coinTexture;
    texture_generate(&coinTexture, "../assets/coin.png", texture::PNG);
    animation coin_animation;
    create_animation(&coin_animation, &coinTexture, 32);

    texture playerTexture;
    texture_generate(&playerTexture, "../assets/player.png", texture::PNG);

    auto animModel = glm::translate(glm::mat4(1.0f), glm::vec3(400.0f, 600.0f, 0.0f));
    animModel = glm::scale(animModel, glm::vec3(300.0f));

    while (true)
    {
        handle_input();
        update_delta_time();
        fill_screen_with_color(21, 21, 21, 1);

        texture_bind(wallTex);
        render_batch(scn.bch, scn.reg_shader);

        texture_bind(ghostTex);
        texture_bind(sqareTex);
        render_batch(batch_tex, simpleShader);

        texture_bind(coinTexture);
        set_uniform_mat4(scn.anim_shader, "model", animModel);
        renderer_set_animation(coin_animation, scn.anim_shader);
        render_animation(scn.anim_shader, scn.anim_vertex);

        swap(window.window);
    }
    return 0;
}

void handle_input()
{
    KeyboardStates = SDL_GetKeyboardState(NULL);
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        switch (e.type)
        {
        case SDL_WINDOWEVENT:
            if (e.window.event == SDL_WINDOWEVENT_CLOSE)
                exit(0);
        case SDL_KEYDOWN:
            if (get_key_down(SDL_SCANCODE_ESCAPE))
                exit(0);
            if (get_key_down(SDL_SCANCODE_C))
            {
                int static current_mode = FILL;
                if (current_mode == FILL)
                {
                    set_rendering_mode(WIREFRAME);
                    current_mode = WIREFRAME;
                }
                else
                {
                    set_rendering_mode(FILL);
                    current_mode = FILL;
                }
            }
        default:
            break;
        }
    }
}
