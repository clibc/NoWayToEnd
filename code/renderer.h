#pragma once
#include "animation.h"
#include "common.h"
#include "shader.h"
#include "vertexBuffer.h"
#include "window.h"

#define swap(x) SDL_GL_SwapWindow(x)

enum render_mode
{
    WIREFRAME,
    FILL
};

void fill_screen_with_color(float r, float g, float b, float a);

void render(shader sh, vertex_buffer &vb);
void render_batch(batch bch, shader batch_shader);

void set_rendering_mode(render_mode mode);
void renderer_set_animation(const animation &anim, shader &sh);
void renderer_set_texture(shader &sh);
void render_animation(shader sh, vertex_buffer &vb);
