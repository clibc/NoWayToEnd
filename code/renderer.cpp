#include "renderer.h"

void FillScreenWithColor(SDL_Window *window,
                         float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Render(shader sh)
{
    // TODO(62bit): takes vertex buffer
    glUseProgram(sh.programID);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void SetRenderingMode(render_mode mode)
{
    if (mode == WIREFRAME)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else if (mode == FILL)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
