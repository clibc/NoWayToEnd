#include "renderer.h"

void FillScreenWithColor(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Render(shader sh, vertex_buffer &vb)
{
    glUseProgram(sh.programID);
    glBindVertexArray(vb.bufferID);
    glDrawArrays(GL_QUADS, 0, 4);
}

void SetRenderingMode(render_mode mode)
{
    if (mode == WIREFRAME)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else if (mode == FILL)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
