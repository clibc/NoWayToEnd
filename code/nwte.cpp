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
    create_window(window, "NoWayToEnd", WINDOW_WIDTH, WINDOW_HEIGHT);

    scene_init(scn);

    texture tex;
    texture_generate(&tex, "../assets/wall.png", texture::PNG);

    texture coinTexture;
    texture_generate(&coinTexture, "../assets/coin.png", texture::PNG);
    animation coin_animation;
    create_animation(&coin_animation, &coinTexture, 32);

    texture playerTexture;
    texture_generate(&playerTexture, "../assets/player.png", texture::PNG);

    glm::mat4 anim_transform = glm::translate(glm::mat4(1.0f), glm::vec3(400.0f, 400.0f, 0.0f));
    anim_transform = glm::scale(anim_transform, glm::vec3(80.0f));

    glm::mat4 player_transform = glm::translate(glm::mat4(1.0f), glm::vec3(480.0f, 400.0f, 0.0f));
    player_transform = glm::scale(player_transform, glm::vec3(80.0f));

    while (true)
    {
        handle_input();
        update_delta_time();
        fill_screen_with_color(21, 21, 21, 1);

        set_uniform_mat4(scn.reg_shader, "model", scn.batch_model);
        texture_bind(tex);
        render_batch(scn.bch, scn.reg_shader);

        for (int i = 0; i < 100; ++i)
        {
            int row = i / COLUMNCOUNT;
            int column = i % ROWCOUNT;
            switch (scn.lvl.cells[i])
            {
            case PLAYER:
            {
                int x = scn.playr.y * CELLSIZE + (CELLSIZE / 2);
                int y = scn.playr.x * CELLSIZE + (CELLSIZE / 2);
                player_transform = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.0f));
                player_transform = glm::scale(player_transform, glm::vec3(CELLSIZE, CELLSIZE, 0.0f));
                set_uniform_mat4(scn.reg_shader, "model", player_transform);
                texture_bind(playerTexture);
                render(scn.reg_shader, scn.reg_vertex);
                break;
            }
            case COIN:
            {
                int x = column * CELLSIZE + (CELLSIZE / 2);
                int y = row * CELLSIZE + (CELLSIZE / 2);
                anim_transform = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.0f));
                anim_transform = glm::scale(anim_transform, glm::vec3(CELLSIZE, CELLSIZE, 0.0f));
                set_uniform_mat4(scn.anim_shader, "model", anim_transform);
                texture_bind(coinTexture);
                renderer_set_animation(coin_animation, scn.anim_shader);
                render_animation(scn.anim_shader, scn.anim_vertex);
                break;
            }

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
            if (get_key_down(SDL_SCANCODE_LEFT) || get_key_down(SDL_SCANCODE_A))
            {
                if (scn.playr.y - 1 >= 0)
                    if (player_can_move(scn.lvl.cells[scn.playr.y - 1 + scn.playr.x * 10]))
                        scn.playr.y -= 1;
            }
            if (get_key_down(SDL_SCANCODE_RIGHT) || get_key_down(SDL_SCANCODE_D))
            {
                if (scn.playr.y + 1 < 10)
                    if (player_can_move(scn.lvl.cells[scn.playr.y + 1 + scn.playr.x * 10]))
                        scn.playr.y += 1;
            }
            if (get_key_down(SDL_SCANCODE_UP) || get_key_down(SDL_SCANCODE_W))
            {
                if (scn.playr.x - 1 >= 0)
                    if (player_can_move(scn.lvl.cells[scn.playr.y + (scn.playr.x - 1) * 10]))
                        scn.playr.x -= 1;
            }
            if (get_key_down(SDL_SCANCODE_DOWN) || get_key_down(SDL_SCANCODE_S))
            {
                if (scn.playr.x + 1 < 10)
                    if (player_can_move(scn.lvl.cells[scn.playr.y + (scn.playr.x + 1) * 10]))
                        scn.playr.x += 1;
            }

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
