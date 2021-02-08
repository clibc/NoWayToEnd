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

    struct VertexI
    {
        glm::vec3 position;
        glm::vec2 texPos;
        float index;
    };

    struct my_batch
    {
        VertexI *vertex_data;
        int *index_data;
        GLuint indexBuffer;
        GLuint vertexBuffer;
        int quadCount;
        int index_count;
    };

    my_batch simpleBatch;
    simpleBatch.quadCount = 9 * 9;
    simpleBatch.index_count = simpleBatch.quadCount * 6;
    simpleBatch.vertex_data = (VertexI *)malloc(sizeof(VertexI) * simpleBatch.quadCount * 4);

    bool index = false;

    int quadPerRow = 9;
    for (int i = 0; i < simpleBatch.quadCount; ++i)
    {
        float x = 0.0f + i % quadPerRow;
        float y = 1.0f * (i / quadPerRow);
        static auto vertex_data = simpleBatch.vertex_data; // To prevent incrementing actual pointer in struct. This is Gonna be replaced by funcion param.

        const float size = 1.0f;
        if (!index)
        {
            VertexI ver1 = {glm::vec3(x, y, 0.0f), glm::vec2(1.0f, 1.0f), 0.0f};
            VertexI ver2 = {glm::vec3(x + size, y, 0.0f), glm::vec2(1.0f, 0.0f), 0.0f};
            VertexI ver3 = {glm::vec3(x + size, y + size, 0.0f), glm::vec2(0.0f, 0.0f), 0.0f};
            VertexI ver4 = {glm::vec3(x, y + size, 0.0f), glm::vec2(0.0f, 1.0f), 0.0f};

            vertex_data[0] = ver1;
            vertex_data[1] = ver2;
            vertex_data[2] = ver3;
            vertex_data[3] = ver4;
            vertex_data += 4;

            index = true;
        }
        else
        {
            VertexI ver1 = {glm::vec3(x, y, 0.0f), glm::vec2(1.0f, 1.0f), 1.0f};
            VertexI ver2 = {glm::vec3(x + size, y, 0.0f), glm::vec2(1.0f, 0.0f), 1.0f};
            VertexI ver3 = {glm::vec3(x + size, y + size, 0.0f), glm::vec2(0.0f, 0.0f), 1.0f};
            VertexI ver4 = {glm::vec3(x, y + size, 0.0f), glm::vec2(0.0f, 1.0f), 1.0f};

            vertex_data[0] = ver1;
            vertex_data[1] = ver2;
            vertex_data[2] = ver3;
            vertex_data[3] = ver4;
            vertex_data += 4;

            index = false;
        }
    }

    {
        int *indices = (int *)malloc(sizeof(int) * simpleBatch.quadCount * 6);
        int count = 0;
        for (int i = 0; i < simpleBatch.quadCount; ++i)
        {
            int index = i * 6;
            indices[index] = count;
            indices[index + 1] = count + 1;
            indices[index + 2] = count + 2;
            indices[index + 3] = count + 2;
            indices[index + 4] = count + 3;
            indices[index + 5] = count;
            count += 4;
        }
        simpleBatch.index_data = indices;
    }

    glCreateBuffers(1, &simpleBatch.indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, simpleBatch.indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * simpleBatch.index_count, simpleBatch.index_data, GL_STATIC_DRAW);

    shader simpleShader;
    create_shader(simpleShader, "../code/shaders/simpleBatch.vs", "../code/shaders/simplefrag.vs");

    vertex_buffer vb;
    vb.vertices = (float *)simpleBatch.vertex_data;
    vb.size = sizeof(VertexI) * 4 * simpleBatch.quadCount;
    generate_dynamic_vertex_buffer(vb);
    simpleBatch.vertexBuffer = vb.bufferID;

    set_vertex_attributef(vb, 0, 3, sizeof(float) * 6, (void *)0);
    set_vertex_attributef(vb, 1, 2, sizeof(float) * 6, (void *)(sizeof(float) * 3));
    set_vertex_attributef(vb, 2, 1, sizeof(float) * 6, (void *)(sizeof(float) * 5));

    auto projection = glm::ortho(0.0f, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT, 0.0f, -1.0f, 1.0f);
    auto model = glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, 10.0f, 0.0f));
    model = glm::scale(model, glm::vec3(80.0f));

    set_uniform_mat4(simpleShader, "projection", projection);
    set_uniform_mat4(simpleShader, "model", model);

    texture wallTex;
    texture_generate(&wallTex, "../assets/wall.png", texture::PNG);
    texture woodTex;
    texture_generate(&woodTex, "../assets/wood.jpg", texture::JPG);

    int samplers[2] = {0, 1};
    auto location = glGetUniformLocation(simpleShader.programID, "textures");
    glUniform1iv(location, 2, samplers);

	// glActiveTexture(GL_TEXTURE0);
	// texture_bind(wallTex);
	// glActiveTexture(GL_TEXTURE1);
	// texture_bind(woodTex);

	
	glBindTextureUnit(0, wallTex.textureID);
	glBindTextureUnit(1, woodTex.textureID);
	
    while (true)
    {
        handle_input();
        update_delta_time();
        fill_screen_with_color(21, 40, 21, 1);

        bind_vertex_buffer_id(simpleBatch.vertexBuffer);
        shader_bind(simpleShader);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, simpleBatch.indexBuffer);
        glDrawElements(GL_TRIANGLES, simpleBatch.quadCount * 6, GL_UNSIGNED_INT, nullptr);

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
