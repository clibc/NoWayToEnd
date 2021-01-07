#include "common.h"
#include "level_loader.h"
#include "renderer.h"
#include "shader.h"
#include "texture.h"
#include "vertexBuffer.h"
#include "window.h"
#include "animation.h"
#include "stb_image.h"
#include "scene.h"

enum cells
{
    EMPTY,
    WALL,
    COIN,
    PLAYER
};

static unsigned int lastTime = 0,
                    currentTime;
static float deltaTime;
void handle_input();
float get_delta_time() { return deltaTime; }

const uint8_t *KeyboardStates;
inline bool get_key_down(SDL_Scancode s) { return KeyboardStates[s]; }

void update_delta_time()
{
    currentTime = SDL_GetTicks();
    deltaTime = ((float)currentTime - (float)lastTime) / 1000.0f;
    lastTime = currentTime;
}

int main(int argc, char *args[])
{
    windowgl_sdl window = {0};
    create_window(window, "NoWayToEnd", WINDOW_WIDTH, WINDOW_HEIGHT);
    scene scn = {0};
    scene_init(scn);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(400.0f, 400.0f, 0.0f));
    model = glm::scale(model, glm::vec3(200.0f, 300.0f, 0.0f));

    set_uniform_mat4(scn.sh, "model", model);
    texture coinTexture;
    texture wallTexture;
    texture_generate(&coinTexture, "../assets/coin.png", texture::PNG);
    texture_generate(&wallTexture, "../assets/wall.png", texture::PNG);

    animation coin_animation;
    create_animation(&coin_animation, &coinTexture, 32);

    level lvl;
    load_level(lvl, "../assets/levels/level1.lvl");
    while (true)
    {
        update_delta_time();
        handle_input();
        fill_screen_with_color(21, 21, 21, 1);

        int row;
        int column;
        for (int i = 0; i < 100; ++i)
        {
            row = i / COLUMNCOUNT;
            column = i % ROWCOUNT;
            int x = column * CELLSIZE + (CELLSIZE / 2);
            int y = row * CELLSIZE + (CELLSIZE / 2);
            switch (lvl.cells[i])
            {
            case WALL:
                model = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.0f));
                model = glm::scale(model, glm::vec3(CELLSIZE, CELLSIZE, 0.0f));
                set_uniform_mat4(scn.sh, "model", model);
                texture_bind(wallTexture);
                renderer_set_texture(scn.sh);
                render(scn.sh, scn.vb);
                break;
            case COIN:
                model = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.0f));
                model = glm::scale(model, glm::vec3(CELLSIZE, CELLSIZE, 0.0f));
                set_uniform_mat4(scn.sh, "model", model);
                texture_bind(coinTexture);
                renderer_set_animation(coin_animation, scn.sh);
                render(scn.sh, scn.vb);
                break;
            default:
                break;
            }
        }
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
            if (get_key_down(SDL_SCANCODE_W))
            {
                debug("exec");
            }

        default:
            break;
        }
    }
}
