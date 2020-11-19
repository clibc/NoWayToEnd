#pragma once
#include "GL/glew.h"
#include "SDL.h"
#include "shader.h"

#define Swap(x) SDL_GL_SwapWindow(x)

enum render_mode
{
    WIREFRAME,
    FILL
};

void FillScreenWithColor(SDL_Window *window,
                         float r, float g, float b, float a);

void Render(shader sh);

void SetRenderingMode(render_mode mode);
