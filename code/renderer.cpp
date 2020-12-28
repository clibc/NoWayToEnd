#include "renderer.h"

void fill_screen_with_color(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void render(shader sh, vertex_buffer &vb)
{
    glUseProgram(sh.programID);
    glBindVertexArray(vb.bufferID);
    glDrawArrays(GL_QUADS, 0, 4);
}

void set_rendering_mode(render_mode mode)
{
    if (mode == WIREFRAME)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else if (mode == FILL)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void render_animation(const animation &anim, shader &sh)
{
    static float current_time = (float)SDL_GetTicks();
    float last_time = 0;
    int clip_index = 0;

    last_time = SDL_GetTicks();

    if (last_time - current_time >= 1000)
    {
        current_time = last_time;

        set_uniform_vec2(sh, "t_positions[0]", anim.clips[(clip_index * 4) + 0]);
        set_uniform_vec2(sh, "t_positions[0]", anim.clips[(clip_index * 4) + 1]);
        set_uniform_vec2(sh, "t_positions[0]", anim.clips[(clip_index * 4) + 2]);
        set_uniform_vec2(sh, "t_positions[0]", anim.clips[(clip_index * 4) + 3]);

        clip_index++;
        if (clip_index == anim.clip_count)
            clip_index = 0;
    }
}
