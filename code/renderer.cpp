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
