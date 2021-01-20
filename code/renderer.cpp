#include "renderer.h"

void fill_screen_with_color(float r, float g, float b, float a)
{
    float p1 = r / 255.0f;
    float p2 = g / 255.0f;
    float p3 = b / 255.0f;
    float p4 = a;
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(p1, p2, p3, p4);
}

void render(shader sh, vertex_buffer &vb)
{
    glUseProgram(sh.programID);
    glBindVertexArray(vb.bufferID);
    glDrawArrays(GL_QUADS, 0, 8);
}

void set_rendering_mode(render_mode mode)
{
    if (mode == WIREFRAME)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else if (mode == FILL)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void renderer_set_animation(const animation &anim, shader &sh)
{
    static float destTime = 0;
    static int clip_index = 0;
    static bool first_clip_displayed = false;

    destTime += get_delta_time();

    if (destTime > ANIMATION_PLAY_TIME)
    {
        destTime = 0.0f;

        set_uniform_vec2(sh, "t_positions[0]", anim.clips[(clip_index * 4) + 0]);
        set_uniform_vec2(sh, "t_positions[1]", anim.clips[(clip_index * 4) + 1]);
        set_uniform_vec2(sh, "t_positions[2]", anim.clips[(clip_index * 4) + 2]);
        set_uniform_vec2(sh, "t_positions[3]", anim.clips[(clip_index * 4) + 3]);

        clip_index++;
        if (clip_index == anim.clip_count)
            clip_index = 0;
    }
    else if (!first_clip_displayed)
    {
        set_uniform_vec2(sh, "t_positions[0]", anim.clips[0]);
        set_uniform_vec2(sh, "t_positions[1]", anim.clips[1]);
        set_uniform_vec2(sh, "t_positions[2]", anim.clips[2]);
        set_uniform_vec2(sh, "t_positions[3]", anim.clips[3]);
        first_clip_displayed = true;
    }
}

void renderer_set_texture(shader &sh)
{
    set_uniform_vec2(sh, "t_positions[0]", glm::vec2(1.0f, 1.0f));
    set_uniform_vec2(sh, "t_positions[1]", glm::vec2(1.0f, 0.0f));
    set_uniform_vec2(sh, "t_positions[2]", glm::vec2(0.0f, 0.0f));
    set_uniform_vec2(sh, "t_positions[3]", glm::vec2(0.0f, 1.0f));
}
