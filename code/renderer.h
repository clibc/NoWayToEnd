#pragma once
#include "GL/glew.h"
#include "SDL.h"
#include "shader.h"
#include "vertexBuffer.h"
#include "window.h"

#define Swap(x) SDL_GL_SwapWindow(x)

enum render_mode
{
    WIREFRAME,
    FILL
};

void FillScreenWithColor(float r, float g, float b, float a);

void Render(shader sh, vertex_buffer &vb);

void SetRenderingMode(render_mode mode);
