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

enum cells
{
    EMPTY,
    WALL,
    COIN,
    PLAYER
};

static unsigned int lastTime = 0, currentTime;
static float deltaTime;
void handle_input();
float get_delta_time() { return deltaTime; }

const uint8_t *KeyboardStates;
inline bool get_key_down(SDL_Scancode s) { return KeyboardStates[s]; }
static player plyr;
static level lvl;

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
    set_uniform_mat4(scn.anim_shader, "model", model);

    texture wallTexture;
    texture_generate(&wallTexture, "../assets/levels/wall.png", texture::PNG);
    texture_bind(wallTexture);

    load_level(lvl, "../assets/levels/level1.lvl");
    while (true)
    {
        handle_input();
        update_delta_time();
        fill_screen_with_color(21, 21, 21, 1);
        glUseProgram(scn.anim_shader.programID);
        glBindVertexArray(scn.anim_vertex.bufferID);
        glDrawArrays(GL_QUADS, 0, 50);
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
                if (plyr.y - 1 >= 0)
                    if (player_can_move(lvl.cells[plyr.y - 1 + plyr.x * 10]))
                        plyr.y -= 1;
            }
            if (get_key_down(SDL_SCANCODE_RIGHT) || get_key_down(SDL_SCANCODE_D))
            {
                if (plyr.y + 1 < 10)
                    if (player_can_move(lvl.cells[plyr.y + 1 + plyr.x * 10]))
                        plyr.y += 1;
            }
            if (get_key_down(SDL_SCANCODE_UP) || get_key_down(SDL_SCANCODE_W))
            {
                if (plyr.x - 1 >= 0)
                    if (player_can_move(lvl.cells[plyr.y + (plyr.x - 1) * 10]))
                        plyr.x -= 1;
            }
            if (get_key_down(SDL_SCANCODE_DOWN) || get_key_down(SDL_SCANCODE_S))
            {
                if (plyr.x + 1 < 10)
                    if (player_can_move(lvl.cells[plyr.y + (plyr.x + 1) * 10]))
                        plyr.x += 1;
            }

        default:
            break;
        }
    }
}
