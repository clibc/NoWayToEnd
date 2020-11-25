#include "window.h"

void create_window(windowgl_sdl &window)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    window.window = SDL_CreateWindow(window.name,
                                     SDL_WINDOWPOS_CENTERED,
                                     SDL_WINDOWPOS_CENTERED,
                                     window.width,
                                     window.height,
                                     SDL_WINDOW_OPENGL);
    SDL_GL_CreateContext(window.window);

    SetAttribs();

    GLenum error = glewInit();
    if (error != GLEW_OK)
    {
        printf("%s", glewGetErrorString(error));
        exit(1);
    }
}
