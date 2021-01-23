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

struct Vertex
{
    glm::vec3 positions;
    glm::vec2 textureCoords;
};

void CreateQuad(Vertex *array, float x, float y)
{
    static float size = 1.0f;

    Vertex ver1 = {glm::vec3(x, y, 0.0f), glm::vec2(1.0f, 1.0f)};
    Vertex ver2 = {glm::vec3(x + size, y, 0.0f), glm::vec2(1.0f, 0.0f)};
    Vertex ver3 = {glm::vec3(x + size, y + size, 0.0f), glm::vec2(0.0f, 0.0f)};
    Vertex ver4 = {glm::vec3(x, y + size, 0.0f), glm::vec2(0.0f, 1.0f)};

    array[0] = ver1;
    array[1] = ver2;
    array[2] = ver3;
    array[3] = ver4;
}

int main(int argc, char *args[])
{
    windowgl_sdl window = {0};
    create_window(window, "NoWayToEnd", WINDOW_WIDTH, WINDOW_HEIGHT);

    const int quadCount = 10;
    Vertex vertices[quadCount * 4];

    for (int i = 0; i < quadCount; ++i)
    {
        CreateQuad(&vertices[i * 4], 0.0f + i % 6, 1.0f * (i / 6));
    }

    vertex_buffer vb;
    vb.vertices = (float *)vertices;
    vb.size = sizeof(Vertex) * 4 * quadCount;
    generate_dynamic_vertex_buffer(vb);
    set_vertex_attributef(vb, 0, 3, sizeof(float) * 5, (void *)0);
    set_vertex_attributef(vb, 1, 2, sizeof(float) * 5, (void *)(sizeof(float) * 3));

    //    int indices[] = {0, 1, 2, 2, 3, 0,
    //               4, 5, 6, 6, 7, 4};

    int indices[quadCount * 6];

    for (int i = 0; i < quadCount; ++i)
    {
        static int count = 0;
        int index = i * 6;
        indices[index] = count;
        indices[index + 1] = count + 1;
        indices[index + 2] = count + 2;
        indices[index + 3] = count + 2;
        indices[index + 4] = count + 3;
        indices[index + 5] = count;
        count += 4;
    }

    GLuint indexBuffer;
    glCreateBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    shader sh;
    create_shader(sh, "../code/shaders/vertex.vs", "../code/shaders/fragment.vs");
    auto projection = glm::ortho(0.0f, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT, 0.0f, -1.0f, 1.0f);
    auto model = glm::translate(glm::mat4(1.0f), glm::vec3(200.0f, 200.0f, 0.0f));
    model = glm::scale(model, glm::vec3(50.0f));

    debug(set_uniform_mat4(sh, "model", model));
    debug(set_uniform_mat4(sh, "projection", projection));

    bind_vertex_buffer(vb);
    glUseProgram(sh.programID);

    texture tex;
    texture_generate(&tex, "../assets/wall.png", texture::PNG);

    while (true)
    {
        handle_input();
        update_delta_time();
        fill_screen_with_color(100, 21, 21, 1);
        glDrawElements(GL_TRIANGLES, quadCount * 6, GL_UNSIGNED_INT, nullptr);
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
